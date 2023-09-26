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
#include <driverlib/rom.h>
#include <driverlib/timer.h>
#include <inc/hw_ints.h>
#include <inc/hw_sysctl.h>
#include <inc/hw_memmap.h>
#include <inc/hw_timer.h>
#include <CFXS/Base/Time.hpp>
#include <CFXS/Base/Debug.hpp>
#include <CFXS/Base/Utility.hpp>
#include <CFXS/Platform/CPU.hpp>
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

namespace CFXS {
    namespace Time {
        volatile Time_t ms = 0;
    }
} // namespace CFXS

bool s_InitializationComplete = false;
bool __cfxs_is_initialization_complete() {
    return s_InitializationComplete;
}

extern void CFXS_LowPriorityLoop();
extern void CFXS_HighPriorityLoop();
extern void CFXS_SystemPriorityLoop();

__weak void __cfxs_app_InitializeModules() {
}
__weak void __cfxs_app_Initialize() {
}

static inline void InitializeTimers() {
#if CFXS_APP_SYSTICK_PERIOD
    SysTickIntRegister(CFXS_SystemPriorityLoop);
    ROM_SysTickPeriodSet(CFXS_APP_SYSTICK_PERIOD);
    ROM_SysTickIntEnable();
    ROM_SysTickEnable();
#else
    #warning CFXS_APP_SYSTICK_PERIOD not defined
#endif

#if defined(CFXS_APP_HIGH_PRIORITY_TIMER_PERIOD) && defined(CFXS_APP_HIGH_PRIORITY_TIMER_INDEX) && \
    defined(CFXS_APP_HIGH_PRIORITY_TIMER_PRIORITY)
    static_assert(CFXS_APP_HIGH_PRIORITY_TIMER_INDEX <= 7, "Invalid timer index");
    static constexpr uint32_t TIMER_PERIPH[] = {SYSCTL_PERIPH_TIMER0,
                                                SYSCTL_PERIPH_TIMER1,
                                                SYSCTL_PERIPH_TIMER2,
                                                SYSCTL_PERIPH_TIMER3,
                                                SYSCTL_PERIPH_TIMER4,
                                                SYSCTL_PERIPH_TIMER5,
                                                SYSCTL_PERIPH_TIMER6,
                                                SYSCTL_PERIPH_TIMER7};
    static constexpr uint32_t TIMER_INT[]    = {
        INT_TIMER0A, INT_TIMER1A, INT_TIMER2A, INT_TIMER3A, INT_TIMER4A, INT_TIMER5A, INT_TIMER6A, INT_TIMER7A};
    static constexpr uint32_t TIMER_BASE[] = {
        TIMER0_BASE, TIMER1_BASE, TIMER2_BASE, TIMER3_BASE, TIMER4_BASE, TIMER5_BASE, TIMER6_BASE, TIMER7_BASE};
    ROM_SysCtlPeripheralEnable(TIMER_PERIPH[CFXS_APP_HIGH_PRIORITY_TIMER_INDEX]);
    while (!ROM_SysCtlPeripheralReady(TIMER_PERIPH[CFXS_APP_HIGH_PRIORITY_TIMER_INDEX])) {
    }

    ROM_TimerConfigure(TIMER_BASE[CFXS_APP_HIGH_PRIORITY_TIMER_INDEX], TIMER_CFG_PERIODIC);
    ROM_IntEnable(TIMER_INT[CFXS_APP_HIGH_PRIORITY_TIMER_INDEX]);
    ROM_IntPrioritySet(TIMER_INT[CFXS_APP_HIGH_PRIORITY_TIMER_INDEX], (CFXS_APP_HIGH_PRIORITY_TIMER_PRIORITY) << 5);
    ROM_TimerIntEnable(TIMER_BASE[CFXS_APP_HIGH_PRIORITY_TIMER_INDEX], TIMER_TIMA_TIMEOUT);
    TimerIntRegister(TIMER_BASE[CFXS_APP_HIGH_PRIORITY_TIMER_INDEX], TIMER_A, []() {
        __mem32(TIMER_BASE[CFXS_APP_HIGH_PRIORITY_TIMER_INDEX] + TIMER_O_ICR) = 0xFFFFFFFF;
        CFXS_HighPriorityLoop();
    });
    ROM_TimerLoadSet(TIMER_BASE[CFXS_APP_HIGH_PRIORITY_TIMER_INDEX], TIMER_A, CFXS_APP_HIGH_PRIORITY_TIMER_PERIOD);
    ROM_TimerEnable(TIMER_BASE[CFXS_APP_HIGH_PRIORITY_TIMER_INDEX], TIMER_A);
#else
    #warning CFXS_APP_HIGH_PRIORITY_TIMER_PERIOD not defined
    #warning CFXS_APP_HIGH_PRIORITY_TIMER_INDEX not defined
    #warning CFXS_APP_HIGH_PRIORITY_TIMER_PRIORITY not defined
#endif
}

static const size_t stackSize       = (size_t)&__STACK_START__ - (size_t)&__STACK_END__;
static const size_t heapSize        = (size_t)&__HEAP_END__ - (size_t)&__HEAP_START__;
static const size_t romDataSize     = (size_t)&__TEXT_END__ - (size_t)&__TEXT_START__;
static const size_t ramInitDataSize = (size_t)&__DATA_END__ - (size_t)&__DATA_START__;
static const size_t ramZeroDataSize = (size_t)&__BSS_END__ - (size_t)&__BSS_START__;
__weak __used void __cfxs_entry_point() {
    InitializeTimers();

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

    __cfxs_app_InitializeModules();
    __cfxs_app_Initialize();

    s_InitializationComplete = true;
    CFXS::CPU::EnableInterrupts();

    while (1 < 2) {
        CFXS_LowPriorityLoop();
    }
}

/////////////////////////////////////////////////////////////
#define MAX_VCO_ENTRIES      2
#define MAX_XTAL_ENTRIES     18
#define PLL_M_TO_REG(mi, mf) ((uint32_t)mi | (uint32_t)(mf << SYSCTL_PLLFREQ0_MFRAC_S))
#define PLL_N_TO_REG(n)      ((uint32_t)(n - 1) << SYSCTL_PLLFREQ1_N_S)
#define PLL_Q_TO_REG(q)      ((uint32_t)(q - 1) << SYSCTL_PLLFREQ1_Q_S)
static constexpr uint32_t g_pppui32XTALtoVCO[MAX_VCO_ENTRIES][MAX_XTAL_ENTRIES][3] = {
    {
        //
        // VCO 320 MHz
        //
        {PLL_M_TO_REG(64, 0), PLL_N_TO_REG(1), PLL_Q_TO_REG(2)},   // 5 MHz
        {PLL_M_TO_REG(62, 512), PLL_N_TO_REG(1), PLL_Q_TO_REG(2)}, // 5.12 MHz
        {PLL_M_TO_REG(160, 0), PLL_N_TO_REG(3), PLL_Q_TO_REG(2)},  // 6 MHz
        {PLL_M_TO_REG(52, 85), PLL_N_TO_REG(1), PLL_Q_TO_REG(2)},  // 6.144 MHz
        {PLL_M_TO_REG(43, 412), PLL_N_TO_REG(1), PLL_Q_TO_REG(2)}, // 7.3728 MHz
        {PLL_M_TO_REG(40, 0), PLL_N_TO_REG(1), PLL_Q_TO_REG(2)},   // 8 MHz
        {PLL_M_TO_REG(39, 64), PLL_N_TO_REG(1), PLL_Q_TO_REG(2)},  // 8.192 MHz
        {PLL_M_TO_REG(32, 0), PLL_N_TO_REG(1), PLL_Q_TO_REG(2)},   // 10 MHz
        {PLL_M_TO_REG(80, 0), PLL_N_TO_REG(3), PLL_Q_TO_REG(2)},   // 12 MHz
        {PLL_M_TO_REG(26, 43), PLL_N_TO_REG(1), PLL_Q_TO_REG(2)},  // 12.288 MHz
        {PLL_M_TO_REG(23, 613), PLL_N_TO_REG(1), PLL_Q_TO_REG(2)}, // 13.56 MHz
        {PLL_M_TO_REG(22, 358), PLL_N_TO_REG(1), PLL_Q_TO_REG(2)}, // 14.318180 MHz
        {PLL_M_TO_REG(20, 0), PLL_N_TO_REG(1), PLL_Q_TO_REG(2)},   // 16 MHz
        {PLL_M_TO_REG(19, 544), PLL_N_TO_REG(1), PLL_Q_TO_REG(2)}, // 16.384 MHz
        {PLL_M_TO_REG(160, 0), PLL_N_TO_REG(9), PLL_Q_TO_REG(2)},  // 18 MHz
        {PLL_M_TO_REG(16, 0), PLL_N_TO_REG(1), PLL_Q_TO_REG(2)},   // 20 MHz
        {PLL_M_TO_REG(40, 0), PLL_N_TO_REG(3), PLL_Q_TO_REG(2)},   // 24 MHz
        {PLL_M_TO_REG(64, 0), PLL_N_TO_REG(5), PLL_Q_TO_REG(2)},   // 25 MHz
    },
    {
        //
        // VCO 480 MHz
        //
        {PLL_M_TO_REG(96, 0), PLL_N_TO_REG(1), PLL_Q_TO_REG(2)},   // 5 MHz
        {PLL_M_TO_REG(93, 768), PLL_N_TO_REG(1), PLL_Q_TO_REG(2)}, // 5.12 MHz
        {PLL_M_TO_REG(80, 0), PLL_N_TO_REG(1), PLL_Q_TO_REG(2)},   // 6 MHz
        {PLL_M_TO_REG(78, 128), PLL_N_TO_REG(1), PLL_Q_TO_REG(2)}, // 6.144 MHz
        {PLL_M_TO_REG(65, 107), PLL_N_TO_REG(1), PLL_Q_TO_REG(2)}, // 7.3728 MHz
        {PLL_M_TO_REG(60, 0), PLL_N_TO_REG(1), PLL_Q_TO_REG(2)},   // 8 MHz
        {PLL_M_TO_REG(58, 608), PLL_N_TO_REG(1), PLL_Q_TO_REG(2)}, // 8.192 MHz
        {PLL_M_TO_REG(48, 0), PLL_N_TO_REG(1), PLL_Q_TO_REG(2)},   // 10 MHz
        {PLL_M_TO_REG(40, 0), PLL_N_TO_REG(1), PLL_Q_TO_REG(2)},   // 12 MHz
        {PLL_M_TO_REG(39, 64), PLL_N_TO_REG(1), PLL_Q_TO_REG(2)},  // 12.288 MHz
        {PLL_M_TO_REG(35, 408), PLL_N_TO_REG(1), PLL_Q_TO_REG(2)}, // 13.56 MHz
        {PLL_M_TO_REG(33, 536), PLL_N_TO_REG(1), PLL_Q_TO_REG(2)}, // 14.318180 MHz
        {PLL_M_TO_REG(30, 0), PLL_N_TO_REG(1), PLL_Q_TO_REG(2)},   // 16 MHz
        {PLL_M_TO_REG(29, 304), PLL_N_TO_REG(1), PLL_Q_TO_REG(2)}, // 16.384 MHz
        {PLL_M_TO_REG(80, 0), PLL_N_TO_REG(3), PLL_Q_TO_REG(2)},   // 18 MHz
        {PLL_M_TO_REG(24, 0), PLL_N_TO_REG(1), PLL_Q_TO_REG(2)},   // 20 MHz
        {PLL_M_TO_REG(20, 0), PLL_N_TO_REG(1), PLL_Q_TO_REG(2)},   // 24 MHz
        {PLL_M_TO_REG(96, 0), PLL_N_TO_REG(5), PLL_Q_TO_REG(2)},   // 25 MHz
    },
};
static constexpr uint32_t g_pui32VCOFrequencies[MAX_VCO_ENTRIES] = {
    160000000, // VCO 320
    240000000, // VCO 480
};
static inline uint32_t _SysCtlMemTimingGet(uint32_t ui32SysClock) {
    if (ui32SysClock == 80000000) {
        return (SYSCTL_MEMTIM0_FBCHT_2_5 | (3 << SYSCTL_MEMTIM0_FWS_S) | SYSCTL_MEMTIM0_EBCHT_2_5 | (3 << SYSCTL_MEMTIM0_EWS_S) |
                SYSCTL_MEMTIM0_MB1);
    } else {
        return (SYSCTL_MEMTIM0_FBCHT_3_5 | (5 << SYSCTL_MEMTIM0_FWS_S) | SYSCTL_MEMTIM0_EBCHT_3_5 | (5 << SYSCTL_MEMTIM0_EWS_S) |
                SYSCTL_MEMTIM0_MB1);
    }
}

static constexpr uint32_t g_pui32Xtals[] = {1000000,  1843200,  2000000,  2457600,  3579545,  3686400,  4000000,  4096000,  4915200,
                                            5000000,  5120000,  6000000,  6144000,  7372800,  8000000,  8192000,  10000000, 12000000,
                                            12288000, 13560000, 14318180, 16000000, 16384000, 18000000, 20000000, 24000000, 25000000};
#define SysCtlXtalCfgToIndex(a) ((a & 0x7c0) >> 6)

static inline uint32_t _SysCtlFrequencyGet(uint32_t ui32Xtal) {
    uint32_t ui32Result;
    uint_fast16_t ui16F1, ui16F2;
    uint_fast16_t ui16PInt, ui16PFract;
    uint_fast8_t ui8Q, ui8N;
    ui16PFract = ((HWREG(SYSCTL_PLLFREQ0) & SYSCTL_PLLFREQ0_MFRAC_M) >> SYSCTL_PLLFREQ0_MFRAC_S);
    ui16PInt   = HWREG(SYSCTL_PLLFREQ0) & SYSCTL_PLLFREQ0_MINT_M;
    ui8Q       = (((HWREG(SYSCTL_PLLFREQ1) & SYSCTL_PLLFREQ1_Q_M) >> SYSCTL_PLLFREQ1_Q_S) + 1);
    ui8N       = (((HWREG(SYSCTL_PLLFREQ1) & SYSCTL_PLLFREQ1_N_M) >> SYSCTL_PLLFREQ1_N_S) + 1);
    ui32Xtal /= (uint32_t)ui8N;
    ui16F1     = ui16PFract / 32;
    ui16F2     = ui16PFract - (ui16F1 * 32);
    ui32Result = ui32Xtal * (uint32_t)ui16PInt;
    ui32Result += (ui32Xtal * (uint32_t)ui16F1) / 32;
    ui32Result += (ui32Xtal * (uint32_t)ui16F2) / 1024;
    ui32Result = ui32Result / (uint32_t)ui8Q;
    return (ui32Result);
}

#define DEF_SysCtlClockFreqSet(ui32Config, clk)                                                                                            \
    {                                                                                                                                      \
        uint32_t ui32SysClock = clk;                                                                                                       \
        int32_t i32Timeout, i32VCOIdx, i32XtalIdx;                                                                                         \
        uint32_t ui32MOSCCTL;                                                                                                              \
        uint32_t ui32Delay;                                                                                                                \
        uint32_t ui32SysDiv, ui32Osc, ui32OscSelect, ui32RSClkConfig;                                                                      \
        i32XtalIdx = SysCtlXtalCfgToIndex(ui32Config);                                                                                     \
        if ((ui32Config & 0x38) == SYSCTL_OSC_INT) {                                                                                       \
            ui32Osc       = 16000000;                                                                                                      \
            ui32OscSelect = SYSCTL_RSCLKCFG_OSCSRC_PIOSC;                                                                                  \
            ui32OscSelect |= SYSCTL_RSCLKCFG_PLLSRC_PIOSC;                                                                                 \
            i32XtalIdx = SysCtlXtalCfgToIndex(SYSCTL_XTAL_16MHZ);                                                                          \
        } else if ((ui32Config & 0x38) == SYSCTL_OSC_INT30) {                                                                              \
            ui32Osc       = 30000;                                                                                                         \
            ui32OscSelect = SYSCTL_RSCLKCFG_OSCSRC_LFIOSC;                                                                                 \
        } else if ((ui32Config & 0x38) == (SYSCTL_OSC_EXT32 & 0x38)) {                                                                     \
            ui32Osc       = 32768;                                                                                                         \
            ui32OscSelect = SYSCTL_RSCLKCFG_OSCSRC_RTC;                                                                                    \
        } else if ((ui32Config & 0x38) == SYSCTL_OSC_MAIN) {                                                                               \
            if ((i32XtalIdx > (SysCtlXtalCfgToIndex(SYSCTL_XTAL_25MHZ))) || (i32XtalIdx < (SysCtlXtalCfgToIndex(SYSCTL_XTAL_5MHZ)))) {     \
            }                                                                                                                              \
            ui32Osc       = g_pui32Xtals[i32XtalIdx];                                                                                      \
            ui32OscSelect = SYSCTL_RSCLKCFG_OSCSRC_MOSC;                                                                                   \
            ui32OscSelect |= SYSCTL_RSCLKCFG_PLLSRC_MOSC;                                                                                  \
            ui32MOSCCTL = HWREG(SYSCTL_MOSCCTL) & ~(SYSCTL_MOSCCTL_OSCRNG | SYSCTL_MOSCCTL_PWRDN | SYSCTL_MOSCCTL_NOXTAL);                 \
            if (i32XtalIdx >= (SysCtlXtalCfgToIndex(SYSCTL_XTAL_10MHZ) - (SysCtlXtalCfgToIndex(SYSCTL_XTAL_5MHZ)))) {                      \
                ui32MOSCCTL |= SYSCTL_MOSCCTL_OSCRNG;                                                                                      \
            }                                                                                                                              \
            HWREG(SYSCTL_MOSCCTL) = ui32MOSCCTL;                                                                                           \
            ui32Delay             = 524288;                                                                                                \
            while ((HWREG(SYSCTL_RIS) & SYSCTL_RIS_MOSCPUPRIS) == 0) {                                                                     \
                ui32Delay--;                                                                                                               \
                                                                                                                                           \
                if (ui32Delay == 0) {                                                                                                      \
                    break;                                                                                                                 \
                }                                                                                                                          \
            }                                                                                                                              \
            if (ui32Delay == 0) {                                                                                                          \
            }                                                                                                                              \
        } else {                                                                                                                           \
            ui32Osc       = 0;                                                                                                             \
            ui32OscSelect = SYSCTL_RSCLKCFG_OSCSRC_PIOSC;                                                                                  \
        }                                                                                                                                  \
        if ((ui32Config & SYSCTL_USE_OSC) == SYSCTL_USE_PLL) {                                                                             \
            if (((ui32Config & 0x38) != SYSCTL_OSC_MAIN) && ((ui32Config & 0x38) != SYSCTL_OSC_INT)) {                                     \
            }                                                                                                                              \
            i32VCOIdx             = (ui32Config >> 24) & 7;                                                                                \
            HWREG(SYSCTL_MEMTIM0) = _SysCtlMemTimingGet(25000000);                                                                         \
            ui32RSClkConfig       = HWREG(SYSCTL_RSCLKCFG) &                                                                               \
                              ~(SYSCTL_RSCLKCFG_PSYSDIV_M | SYSCTL_RSCLKCFG_OSCSRC_M | SYSCTL_RSCLKCFG_PLLSRC_M | SYSCTL_RSCLKCFG_USEPLL); \
            ui32RSClkConfig |= SYSCTL_RSCLKCFG_MEMTIMU;                                                                                    \
            HWREG(SYSCTL_RSCLKCFG) = ui32RSClkConfig;                                                                                      \
            i32XtalIdx -= SysCtlXtalCfgToIndex(SYSCTL_XTAL_5MHZ);                                                                          \
            ui32SysDiv = (g_pui32VCOFrequencies[i32VCOIdx] + ui32SysClock - 1) / ui32SysClock;                                             \
            HWREG(SYSCTL_RSCLKCFG) |= ui32OscSelect;                                                                                       \
            HWREG(SYSCTL_PLLFREQ1) = g_pppui32XTALtoVCO[i32VCOIdx][i32XtalIdx][1];                                                         \
            HWREG(SYSCTL_PLLFREQ1) |= PLL_Q_TO_REG(ui32SysDiv);                                                                            \
            HWREG(SYSCTL_PLLFREQ0) = (g_pppui32XTALtoVCO[i32VCOIdx][i32XtalIdx][0] | (HWREG(SYSCTL_PLLFREQ0) & SYSCTL_PLLFREQ0_PLLPWR));   \
            ui32SysClock           = _SysCtlFrequencyGet(ui32Osc) / 2;                                                                     \
            HWREG(SYSCTL_MEMTIM0)  = _SysCtlMemTimingGet(ui32SysClock);                                                                    \
            if (HWREG(SYSCTL_PLLFREQ0) & SYSCTL_PLLFREQ0_PLLPWR) {                                                                         \
                HWREG(SYSCTL_RSCLKCFG) |= SYSCTL_RSCLKCFG_NEWFREQ;                                                                         \
            } else {                                                                                                                       \
                HWREG(SYSCTL_PLLFREQ0) |= SYSCTL_PLLFREQ0_PLLPWR;                                                                          \
            }                                                                                                                              \
            for (i32Timeout = 32768; i32Timeout > 0; i32Timeout--) {                                                                       \
                if ((HWREG(SYSCTL_PLLSTAT) & SYSCTL_PLLSTAT_LOCK)) {                                                                       \
                    break;                                                                                                                 \
                }                                                                                                                          \
            }                                                                                                                              \
            if (i32Timeout) {                                                                                                              \
                ui32RSClkConfig = HWREG(SYSCTL_RSCLKCFG);                                                                                  \
                ui32RSClkConfig |= (1 << SYSCTL_RSCLKCFG_PSYSDIV_S) | ui32OscSelect | SYSCTL_RSCLKCFG_USEPLL;                              \
                ui32RSClkConfig |= SYSCTL_RSCLKCFG_MEMTIMU;                                                                                \
                HWREG(SYSCTL_RSCLKCFG) = ui32RSClkConfig;                                                                                  \
            } else {                                                                                                                       \
                ui32SysClock = 0;                                                                                                          \
            }                                                                                                                              \
        } else {                                                                                                                           \
            HWREG(SYSCTL_MEMTIM0) = _SysCtlMemTimingGet(16000000);                                                                         \
            HWREG(SYSCTL_PLLFREQ0) &= ~SYSCTL_PLLFREQ0_PLLPWR;                                                                             \
            ui32RSClkConfig = HWREG(SYSCTL_RSCLKCFG);                                                                                      \
            ui32RSClkConfig &= ~(SYSCTL_RSCLKCFG_OSYSDIV_M | SYSCTL_RSCLKCFG_OSCSRC_M | SYSCTL_RSCLKCFG_USEPLL);                           \
            ui32RSClkConfig |= SYSCTL_RSCLKCFG_MEMTIMU;                                                                                    \
            HWREG(SYSCTL_RSCLKCFG) = ui32RSClkConfig;                                                                                      \
            if (ui32SysClock == 0) {                                                                                                       \
                ui32SysDiv = 0;                                                                                                            \
            } else {                                                                                                                       \
                ui32SysDiv = ui32Osc / ui32SysClock;                                                                                       \
                if (ui32SysDiv != 0) {                                                                                                     \
                    ui32SysDiv -= 1;                                                                                                       \
                }                                                                                                                          \
                ui32SysClock = ui32Osc / (ui32SysDiv + 1);                                                                                 \
            }                                                                                                                              \
            HWREG(SYSCTL_MEMTIM0) = _SysCtlMemTimingGet(ui32SysClock);                                                                     \
            ui32RSClkConfig       = HWREG(SYSCTL_RSCLKCFG);                                                                                \
            ui32RSClkConfig |= (ui32SysDiv << SYSCTL_RSCLKCFG_OSYSDIV_S) | ui32OscSelect;                                                  \
            ui32RSClkConfig |= SYSCTL_RSCLKCFG_MEMTIMU;                                                                                    \
            HWREG(SYSCTL_RSCLKCFG) = ui32RSClkConfig;                                                                                      \
        }                                                                                                                                  \
        HWREG(SYSCTL_RSCLKCFG) &= ~(SYSCTL_RSCLKCFG_OSCSRC_M);                                                                             \
    }

// Default before data init
__used __weak void __cfxs_init() {
    // Disable all configurable interrupts
    __mem32(NVIC_DIS0) = 0xFFFFFFFF;
    __mem32(NVIC_DIS1) = 0xFFFFFFFF;
    __mem32(NVIC_DIS2) = 0xFFFFFFFF;
    __mem32(NVIC_DIS3) = 0xFFFFFFFF;
    __mem32(NVIC_DIS4) = 0xFFFFFFFF;

// Enable FPU
// __mem32(NVIC_CPAC) = ((__mem32(NVIC_CPAC) & ~(NVIC_CPAC_CP10_M | NVIC_CPAC_CP11_M)) | NVIC_CPAC_CP10_FULL | NVIC_CPAC_CP11_FULL);

// Configure clock (for fast init)
#ifdef TARGET_IS_TM4C129_RA2
    DEF_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480), CFXS::CPU::CLOCK_FREQUENCY);
#else
    DEF_SysCtlClockSet(SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_SYSDIV_2_5);
#endif

    // CFXS::CPU::EnableCycleCounter();
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

    // // fill stack pattern
    // volatile auto sp = (uint32_t*)CFXS::CPU::__GetSP();
    // for (uint32_t* wptr = (uint32_t*)&__STACK_END__; wptr < sp; wptr++) {
    //     *wptr = 0x55555555;
    // }

    // // fill heap pattern
    // for (uint32_t* wptr = (uint32_t*)&__HEAP_START__; wptr < (uint32_t*)&__HEAP_END__; wptr++) {
    //     *wptr = 0xEAEAEAEA;
    // }

    // CFXS::MemoryManager::Initialize();

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
extern "C" __noreturn __used void __cfxs_reset() {
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

__weak void __interrupt_NMI() {
    CFXS_BREAK();
    CFXS::CPU::Reset();
}

__weak void __interrupt_HardFault() {
    CFXS_BREAK();
    CFXS::CPU::Reset();
}

__weak void __interrupt_Unhandled() {
    CFXS_BREAK();
    CFXS::CPU::Reset();
}

__vector_table const CFXS::CPU::VectorTable_Minimal<&__STACK_START__, __cfxs_reset, __interrupt_NMI> g_VectorTable = []() constexpr {
    std::remove_cv<decltype(g_VectorTable)>::type vt;
    vt._HardFault = __interrupt_HardFault;
    vt._NMI       = __interrupt_NMI;
    return vt;
}();