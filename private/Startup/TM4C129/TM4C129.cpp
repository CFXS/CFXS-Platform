// ---------------------------------------------------------------------
// CFXS Framework Platform Module <https://github.com/CFXS/CFXS-Platform>
// Copyright (C) 2022 | CFXS / Rihards Veips
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>
// ---------------------------------------------------------------------
// [CFXS] //
#include <type_traits>
#include <driverlib/sysctl.h>
#include <driverlib/systick.h>
#include <CFXS/Base/Time.hpp>
#include <CFXS/Base/Debug.hpp>
#include <CFXS/Base/Utility.hpp>
#include <CFXS/Platform/CPU.hpp>
#include <CFXS/Platform/App.hpp>
#include <CFXS/Platform/Heap/MemoryManager.hpp>

// Empty handler for Tiva lib ASSERT
extern "C" __weak void __error__(char* pcFilename, uint32_t ui32Line) {
    // asm volatile("bkpt");
    CFXS_printf(ANSI_RED "driverlib assert \"%s\":%lu\n", pcFilename, ui32Line);
}

/////////////////////////////////////////////////////////////
// Externals
extern const uint32_t __STACK_START__;      // Stack base is higher in memory than stack end
extern const uint32_t __STACK_END__;        // Stack limit (start of heap)
extern const uint32_t __HEAP_START__;       // Heap base
extern const uint32_t __HEAP_END__;         // End of heap (should be end of RAM)
extern const uint32_t __TEXT_START__;       // Start of ROM data
extern const uint32_t __TEXT_END__;         // End of ROM data
extern const uint32_t __DATA_START__;       // Const init target base
extern const uint32_t __DATA_END__;         // Const init target end
extern const uint32_t __CONST_DATA_START__; // Location of const init source data in flash
extern const uint32_t __BSS_START__;        // Zero init data
extern const uint32_t __BSS_END__;
extern void (*const __PREINIT_ARRAY_START__[])(void);
extern void (*const __PREINIT_ARRAY_END__[])(void);
extern void (*const __INIT_ARRAY_START__[])(void);
extern void (*const __INIT_ARRAY_END__[])(void);
extern void (*const __FINI_ARRAY_START__[])(void);
extern void (*const __FINI_ARRAY_END__[])(void);
/////////////////////////////////////////////////////////////
// Default startup

extern const CFXS::AppDescriptor e_AppDescriptor;
namespace CFXS {
    namespace Time {
        volatile Time_t ms = 0;
    }

    namespace Platform {
        extern void CoreInit(const CFXS::AppDescriptor& appDesc);
    }
} // namespace CFXS

bool s_InitializationComplete = false;
bool __cfxs_is_initialization_complete() {
    return s_InitializationComplete;
}

__weak __used void __cfxs_entry_point() {
    extern void CFXS_LowPriorityLoop();
    static const size_t stackSize       = (size_t)&__STACK_START__ - (size_t)&__STACK_END__;
    static const size_t heapSize        = (size_t)&__HEAP_END__ - (size_t)&__HEAP_START__;
    static const size_t romDataSize     = (size_t)&__TEXT_END__ - (size_t)&__TEXT_START__;
    static const size_t ramInitDataSize = (size_t)&__DATA_END__ - (size_t)&__DATA_START__;
    static const size_t ramZeroDataSize = (size_t)&__BSS_END__ - (size_t)&__BSS_START__;

    CFXS::Platform::CoreInit(e_AppDescriptor);

    CFXS_printf("[" CFXS_PROJECT_NAME " " CFXS_PROJECT_VERSION_STRING "]\n");
    CFXS_printf(" - ROM Data:      %ukB\t[0x%08X - 0x%08X] (%u bytes)\n",
                romDataSize / 1024,
                (size_t)&__TEXT_START__,
                (size_t)&__TEXT_END__,
                romDataSize);
    CFXS_printf(" - RAM Init Data: %ukB\t[0x%08X - 0x%08X] (%u bytes)\n",
                ramInitDataSize / 1024,
                (size_t)&__DATA_START__,
                (size_t)&__DATA_END__,
                ramInitDataSize);
    CFXS_printf(" - RAM Zero Data: %ukB\t[0x%08X - 0x%08X] (%u bytes)\n",
                ramZeroDataSize / 1024,
                (size_t)&__BSS_START__,
                (size_t)&__BSS_END__,
                ramZeroDataSize);
    CFXS_printf(" - Stack:         %ukB\t[0x%08X - 0x%08X] (%u bytes)\n",
                stackSize / 1024,
                (size_t)&__STACK_END__,
                (size_t)&__STACK_START__,
                stackSize);
    CFXS_printf(" - Heap:          %ukB\t[0x%08X - 0x%08X] (%u bytes)\n",
                heapSize / 1024,
                (size_t)&__HEAP_START__,
                (size_t)&__HEAP_END__,
                heapSize);

    CFXS::SafeCall(e_AppDescriptor.moduleInit);
    CFXS::SafeCall(e_AppDescriptor.postModuleInit);

    s_InitializationComplete = true;
    CFXS::CPU::EnableInterrupts();

    while (1 < 2) {
        CFXS_LowPriorityLoop();
    }
}

/////////////////////////////////////////////////////////////

// Default before data init
__used __weak void __cfxs_init() {
    // Disable all configurable interrupts
    __mem32(NVIC_DIS0) = 0xFFFFFFFF;
    __mem32(NVIC_DIS1) = 0xFFFFFFFF;
    __mem32(NVIC_DIS2) = 0xFFFFFFFF;
    __mem32(NVIC_DIS3) = 0xFFFFFFFF;
    __mem32(NVIC_DIS4) = 0xFFFFFFFF;

    // Enable FPU
    __mem32(NVIC_CPAC) = ((__mem32(NVIC_CPAC) & ~(NVIC_CPAC_CP10_M | NVIC_CPAC_CP11_M)) | NVIC_CPAC_CP10_FULL | NVIC_CPAC_CP11_FULL);

    // Configure clock (for fast init)
    SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480), CFXS::CPU::CLOCK_FREQUENCY);

    CFXS::CPU::EnableCycleCounter();
}

// Default data init
__used __weak void __cfxs_data_init() {
    // const init
    auto pui32Src = &__CONST_DATA_START__;
    for (uint32_t* pui32Dest = (uint32_t*)&__DATA_START__; pui32Dest < &__DATA_END__;) {
        *pui32Dest++ = *pui32Src++;
    }

    // zero init
    asm volatile("    ldr     r0, =__BSS_START__ \n"
                 "    ldr     r1, =__BSS_END__   \n"
                 "    mov     r2, #0             \n"
                 "zeroinit_loop:                 \n"
                 "        cmp     r0, r1         \n"
                 "        it      lt             \n"
                 "        strlt   r2, [r0], #4   \n"
                 "        blt     zeroinit_loop    ");

    // fill stack pattern
    volatile auto sp = (uint32_t*)CFXS::CPU::__GetSP();
    for (uint32_t* wptr = (uint32_t*)&__STACK_END__; wptr < sp; wptr++) {
        *wptr = 0x55555555;
    }

    // fill heap pattern
    for (uint32_t* wptr = (uint32_t*)&__HEAP_START__; wptr < (uint32_t*)&__HEAP_END__; wptr++) {
        *wptr = 0xEAEAEAEA;
    }

    CFXS::MemoryManager::Initialize();

    // ctor init
    for (auto i = 0; i < __PREINIT_ARRAY_END__ - __PREINIT_ARRAY_START__; i++) {
        __PREINIT_ARRAY_START__[i]();
    }

    for (auto i = 0; i < __INIT_ARRAY_END__ - __INIT_ARRAY_START__; i++) {
        __INIT_ARRAY_START__[i]();
    }
}

// First instructions to be executed (do JTAG lock or whatever else)
__weak void __cfxs_startup() {
}

// Startup entry point (extern "C" for LinkerScript ENTRY)
__c_func __noreturn __used void __cfxs_reset() {
    __cfxs_startup();
    CFXS::CPU::DisableInterrupts();

    __cfxs_init();        // disable interrupt bits + configure clock
    __cfxs_data_init();   // const/constructor init
    __cfxs_entry_point(); // go to main

    CFXS_BREAK();

    CFXS::CPU::Reset();
    while (1 < 2) {
    }
}

////////////////////////////////////////////////////////////////////////////////////////
// Overcomplicated Default Vector Table

__c_func __weak void __interrupt_NMI() {
    CFXS_BREAK();
    CFXS::CPU::Reset();
}

__c_func __weak void __interrupt_HardFault() {
    CFXS_BREAK();
    CFXS::CPU::Reset();
}

__c_func __weak void __interrupt_Unhandled() {
    CFXS_BREAK();
    CFXS::CPU::Reset();
}

__vector_table const CFXS::CPU::VectorTable<&__STACK_START__, __cfxs_reset, __interrupt_NMI> g_VectorTable = []() constexpr {
    std::remove_cv<decltype(g_VectorTable)>::type vt;
    vt._HardFault = __interrupt_HardFault;
    vt._NMI       = __interrupt_NMI;
    return vt;
}();