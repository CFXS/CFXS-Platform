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
#include <inc/hw_nvic.h>
#include <inc/hw_types.h>
#include "Cortex_M.hpp"

namespace CFXS::CPU {

    static constexpr size_t CLOCK_FREQUENCY      = CFXS_CPU_CLOCK_FREQUENCY;
    static constexpr size_t CYCLES_PER_MS        = CLOCK_FREQUENCY / 1000;
    static constexpr size_t CYCLES_PER_USEC      = CLOCK_FREQUENCY / 1000000;
    static constexpr float CYCLES_PER_MS_FLOAT   = CLOCK_FREQUENCY / 1000.0f;
    static constexpr float CYCLES_PER_USEC_FLOAT = CLOCK_FREQUENCY / 1000000.0f;

    /// Reset CPU
    static __always_inline __noreturn void Reset() {
        HWREG(NVIC_APINT) = NVIC_APINT_VECTKEY | NVIC_APINT_SYSRESETREQ;
        while (1 < 2) {
        }
    }

    /// Enable global interrupts
    static __always_inline void EnableInterrupts() {
        asm("cpsie i" ::: "memory");
    }

    /// Disable global interrupts
    static __always_inline void DisableInterrupts() {
        asm("cpsid i" ::: "memory");
    }

    /// Are global interrupts enabled
    /// \returns true if global interrupts are enabled
    static __always_inline bool AreInterruptsEnabled() {
        return CFXS::CPU::__GetPRIMASK();
    }

} // namespace CFXS::CPU