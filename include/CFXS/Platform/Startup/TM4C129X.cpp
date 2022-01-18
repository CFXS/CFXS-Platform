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
#if defined(CFXS_DEVICE_CLASS_TM4C129X)
#include <type_traits>
#include <driverlib_includes.hpp>
#include <CFXS/Base/Cortex_M/VectorTable_TM4C129X.hpp>
#include <CFXS/Base/CPU.hpp>

// Empty handler for Tiva lib ASSERT
extern "C" __weak void __error__(char *pcFilename, uint32_t ui32Line) {
    __asm__("bkpt");
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
// Default Handlers

__interrupt void __isr_NMI(void) {
    __asm__("bkpt");
}

__interrupt void __isr_HardFault(void) {
    __asm__("bkpt");
}

__interrupt void __isr_Default(void) {
    __asm__("bkpt");
}

__interrupt __noreturn __used void __Reset() {
    CFXS::CPU::DisableInterrupts();

    // Enable FPU
    HWREG(NVIC_CPAC) = ((HWREG(NVIC_CPAC) & ~(NVIC_CPAC_CP10_M | NVIC_CPAC_CP11_M)) | NVIC_CPAC_CP10_FULL | NVIC_CPAC_CP11_FULL);

    // Configure clock (for fast init)
    SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480), CFXS::CPU::CLOCK_FREQUENCY);

    // const init
    auto pui32Src = &__TEXT_END__;
    for (auto pui32Dest = &__DATA_START__; pui32Dest < &__DATA_END__;) {
        *pui32Dest++ = *pui32Src++;
    }

    // zero init
    __asm__("    ldr     r0, =__BSS_START__ \n"
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

    __cfxs_entry_point();

    __asm__("bkpt");

    HWREG(NVIC_APINT) = NVIC_APINT_VECTKEY | NVIC_APINT_SYSRESETREQ;
    while (1 < 2) {
    }
}

////////////////////////////////////////////////////////////////////////////////////////
// Overcomplicated Default Vector Table

__vector_table __used const CFXS::Cortex_M::VectorTable_TM4C129X<&__STACK_BASE__, __Reset, __isr_Default> g_VectorTable = []() constexpr {
    std::remove_cv<decltype(g_VectorTable)>::type vt;
    vt.isr_HardFault = __isr_HardFault;
    vt.isr_NMI       = __isr_NMI;
    return vt;
}
();
#endif