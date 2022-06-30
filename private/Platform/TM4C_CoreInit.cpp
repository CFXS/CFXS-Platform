// [CFXS] //
#include <CFXS/Base/Debug.hpp>
#include <CFXS/Platform/TM4C/CoreInit.hpp>
#include <CFXS/Platform/App.hpp>
#include <driverlib/sysctl.h>
#include <driverlib/systick.h>
#include <driverlib/timer.h>
#include <driverlib/interrupt.h>
#include <inc/hw_timer.h>
#include <inc/hw_memmap.h>
#include <inc/hw_ints.h>

extern void CFXS_SystemPriorityLoop();
extern void CFXS_HighPriorityLoop();

static const size_t TIMER_PERIPH[] = {
    SYSCTL_PERIPH_TIMER0,
    SYSCTL_PERIPH_TIMER1,
    SYSCTL_PERIPH_TIMER2,
    SYSCTL_PERIPH_TIMER3,
    SYSCTL_PERIPH_TIMER4,
    SYSCTL_PERIPH_TIMER5,
    SYSCTL_PERIPH_TIMER6,
    SYSCTL_PERIPH_TIMER7,
};
static const size_t TIMER_BASE[] = {
    TIMER0_BASE,
    TIMER1_BASE,
    TIMER2_BASE,
    TIMER3_BASE,
    TIMER4_BASE,
    TIMER5_BASE,
    TIMER6_BASE,
    TIMER7_BASE,
};
static const size_t TIMER_INT[] = {
    INT_TIMER0A,
    INT_TIMER1A,
    INT_TIMER2A,
    INT_TIMER3A,
    INT_TIMER4A,
    INT_TIMER5A,
    INT_TIMER6A,
    INT_TIMER7A,
};
static const CFXS::VoidFunction_t TIMER_CALLBACK[] = {
    []() {
        TimerIntClear(TIMER_BASE[0], 0xFFFFFFFF);
        CFXS_HighPriorityLoop();
    },
    []() {
        TimerIntClear(TIMER_BASE[1], 0xFFFFFFFF);
        CFXS_HighPriorityLoop();
    },
    []() {
        TimerIntClear(TIMER_BASE[2], 0xFFFFFFFF);
        CFXS_HighPriorityLoop();
    },
    []() {
        TimerIntClear(TIMER_BASE[3], 0xFFFFFFFF);
        CFXS_HighPriorityLoop();
    },
    []() {
        TimerIntClear(TIMER_BASE[4], 0xFFFFFFFF);
        CFXS_HighPriorityLoop();
    },
    []() {
        TimerIntClear(TIMER_BASE[5], 0xFFFFFFFF);
        CFXS_HighPriorityLoop();
    },
    []() {
        TimerIntClear(TIMER_BASE[6], 0xFFFFFFFF);
        CFXS_HighPriorityLoop();
    },
    []() {
        TimerIntClear(TIMER_BASE[7], 0xFFFFFFFF);
        CFXS_HighPriorityLoop();
    },
};

namespace CFXS::Platform {

    void CoreInit(const AppDescriptor& appDesc) {
        auto& platformDesc = *static_cast<const TM4C::CoreInitDescriptor*>(appDesc.platformInitDescriptor);
        CFXS_ASSERT(platformDesc.splitHighPriorityTimer == 0, "Split timer not implemented");

        if (appDesc.systemPriorityLoopPeriod) {
            SysTickIntRegister(CFXS_SystemPriorityLoop);
            SysTickPeriodSet(appDesc.systemPriorityLoopPeriod);
            SysTickIntEnable();
            SysTickEnable();
        }

        if (appDesc.highPriorityLoopPeriod) {
            CFXS_ASSERT(platformDesc.splitHighPriorityTimer <= 7, "Invalid timer index");
            auto timerIndex = platformDesc.splitHighPriorityTimer;
            SysCtlPeripheralEnable(TIMER_PERIPH[timerIndex]);
            while (!SysCtlPeripheralReady(TIMER_PERIPH[timerIndex])) {
            }

            TimerConfigure(TIMER_BASE[timerIndex], TIMER_CFG_PERIODIC);
            IntEnable(TIMER_INT[timerIndex]);
            IntPrioritySet(TIMER_INT[timerIndex], appDesc.highPriorityLoopPriority << 5);
            TimerIntEnable(TIMER_BASE[timerIndex], TIMER_TIMA_TIMEOUT);
            TimerIntRegister(TIMER_BASE[timerIndex], TIMER_A, TIMER_CALLBACK[timerIndex]);
            TimerLoadSet(TIMER_BASE[timerIndex], TIMER_A, appDesc.highPriorityLoopPeriod);
            TimerEnable(TIMER_BASE[timerIndex], TIMER_A);
        }
    }

} // namespace CFXS::Platform