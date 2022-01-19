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
#include <CFXS/Base/Debug.hpp>
#include <CFXS/Base/Cortex_M/VectorTable_TM4C129X.hpp>
#include <CFXS/Platform/CPU.hpp>
#include <driverlib/sysctl.h>

// Empty handler for Tiva lib ASSERT
extern "C" __weak void __error__(char *pcFilename, uint32_t ui32Line) {
    asm volatile("bkpt");
}

/////////////////////////////////////////////////////////////
// Externals
extern const uint32_t __STACK_BASE__;
extern const uint32_t __TEXT_END__;
extern uint32_t __DATA_START__;
extern const uint32_t __DATA_END__;
extern const uint32_t __BSS_START__;
extern const uint32_t __BSS_END__;
extern void (*const __PREINIT_ARRAY_START__[])(void);
extern void (*const __PREINIT_ARRAY_END__[])(void);
extern void (*const __INIT_ARRAY_START__[])(void);
extern void (*const __INIT_ARRAY_END__[])(void);
extern void (*const __FINI_ARRAY_START__[])(void);
extern void (*const __FINI_ARRAY_END__[])(void);
/////////////////////////////////////////////////////////////
// Default startup

__weak __used void __cfxs_entry_point() {
    extern int main();
    main();
}

/////////////////////////////////////////////////////////////

// Default before data init
__used __weak void __cfxs_init() {
    // Disable all configurable interrupts
    HWREG(NVIC_DIS0) = 0xFFFFFFFF;
    HWREG(NVIC_DIS1) = 0xFFFFFFFF;
    HWREG(NVIC_DIS2) = 0xFFFFFFFF;
    HWREG(NVIC_DIS3) = 0xFFFFFFFF;
    HWREG(NVIC_DIS4) = 0xFFFFFFFF;

    // Enable FPU
    HWREG(NVIC_CPAC) = ((HWREG(NVIC_CPAC) & ~(NVIC_CPAC_CP10_M | NVIC_CPAC_CP11_M)) | NVIC_CPAC_CP10_FULL | NVIC_CPAC_CP11_FULL);

    // Configure clock (for fast init)
    SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480), CFXS::CPU::CLOCK_FREQUENCY);
}

// Default data init
__used __weak void __cfxs_data_init() {
    // const init
    auto pui32Src = &__TEXT_END__;
    for (auto pui32Dest = &__DATA_START__; pui32Dest < &__DATA_END__;) {
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

    // ctor init
    for (auto i = 0; i < __PREINIT_ARRAY_END__ - __PREINIT_ARRAY_START__; i++) {
        __PREINIT_ARRAY_START__[i]();
    }

    for (auto i = 0; i < __INIT_ARRAY_END__ - __INIT_ARRAY_START__; i++) {
        __INIT_ARRAY_START__[i]();
    }
}

// Startup entry point
__interrupt __noreturn __used void __cfxs_reset() {
    CFXS::CPU::DisableInterrupts();

    __cfxs_init();        // Disable interrupt bits + configure clock
    __cfxs_data_init();   // Const/constructor init
    __cfxs_entry_point(); // Go to main

    CFXS_BREAK();

    CFXS::CPU::Reset();
}

////////////////////////////////////////////////////////////////////////////////////////
// Overcomplicated Default Vector Table

__interrupt __weak void __cfxs_isr_NMI(void) {
    CFXS_BREAK();
    CFXS::CPU::Reset();
}

__interrupt __weak void __cfxs_isr_HardFault(void) {
    CFXS_BREAK();
    CFXS::CPU::Reset();
}

__interrupt __weak void __cfxs_isr_Unhandled(void) {
    CFXS_BREAK();
    CFXS::CPU::Reset();
}

__vector_table const CFXS::Cortex_M::VectorTable_TM4C129X<&__STACK_BASE__, __cfxs_reset, __cfxs_isr_Unhandled> g_VectorTable =
    []() constexpr {
    std::remove_cv<decltype(g_VectorTable)>::type vt;
    vt.isr_HardFault = __cfxs_isr_HardFault;
    vt.isr_NMI       = __cfxs_isr_NMI;
    return vt;
}
();