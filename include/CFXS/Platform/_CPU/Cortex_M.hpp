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
#pragma once
#include "../ClocksAndCycles.hpp"

#ifdef CFXS_CORE_CORTEX_M4
    #include "Registers/Cortex_M4.hpp"
#else
    #error unknown core
#endif

namespace CFXS::CPU {

    /// Read PRIMASK register
    static __always_inline size_t __GetPRIMASK() {
        size_t val;
        asm volatile("mrs %0, primask" : "=r"(val));
        return val;
    }

    /// Read BASEPRI register
    static __always_inline size_t __GetBASEPRI() {
        size_t val;
        asm volatile("mrs %0, basepri" : "=r"(val));
        return val;
    }

    /// Read SP register
    static __always_inline size_t __GetSP() {
        size_t val;
        asm volatile("mrs %0, msp" : "=r"(val));
        return val;
    }

    /// Read LR register
    static __always_inline size_t __GetLR() {
        size_t val;
        asm volatile("mov %0, lr" : "=r"(val));
        return val;
    }

    /// Read PC register
    static __always_inline size_t __GetPC() {
        size_t val;
        asm volatile("mov %0, pc" : "=r"(val));
        return val;
    }

    /// Count trailing zeros
    static __always_inline uint32_t __CTZ(uint32_t x) {
        uint32_t res = 0;
        asm("rbit %[dest], %[val]" : [dest] "=r"(res) : [val] "r"(x));
        asm("clz %[dest], %[val]" : [dest] "=r"(res) : [val] "r"(res));
        return res;
    }

    /// Count leading zeros
    static __always_inline uint32_t __CLZ(uint32_t x) {
        uint32_t res = 0;
        asm("clz %[dest], %[val]" : [dest] "=r"(res) : [val] "r"(res));
        return res;
    }

    /// Block for x cycles
    void __naked BlockingCycles(uint32_t cycles);

    /// Block for x miroseconds
    void __always_inline BlockingMicroseconds(uint32_t usec) {
        BlockingCycles(usec * GetCyclesPerMicrosecond());
    }

    /// Block for x milliseconds
    void __always_inline BlockingMilliseconds(uint32_t ms) {
        BlockingCycles(ms * GetCyclesPerMillisecond());
    }

    /// Enable cycle counter (DWT_CTRL)
    void __always_inline EnableCycleCounter() {
        Registers::DWT::DWT_CTRL->CYCCNTENA = true;
    }

    /// Disable cycle counter (DWT_CTRL)
    void __always_inline DisableCycleCounter() {
        Registers::DWT::DWT_CTRL->CYCCNTENA = false;
    }

    /// Get cycle count (DWT_CYCCNT)
    size_t __always_inline GetCycleCount() {
        return Registers::DWT::DWT_CYCCNT->CYCCNT;
    }

} // namespace CFXS::CPU
