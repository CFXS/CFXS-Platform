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
#include "Cortex_M.hpp"
#include <CFXS/Base/Memory.hpp>

namespace CFXS::CPU {

    /// Reset CPU
    inline __noreturn void Reset() {
        __mem32(0xE000ED0C) = 0x05FA0000 | 0x00000004;
        while (1 < 2) {
        }
    }

    /// Enable global interrupts
    inline void EnableInterrupts() {
        asm("cpsie i" ::: "memory");
    }

    /// Disable global interrupts
    inline void DisableInterrupts() {
        asm("cpsid i" ::: "memory");
    }

    /// Are global interrupts enabled
    /// \returns true if global interrupts are enabled
    inline bool AreInterruptsEnabled() {
        return !CFXS::CPU::__GetPRIMASK();
    }

    /// Set interrupt handler
    inline void SetInterruptHandler(int offset, CFXS::VoidFunction_t handler) {
        CFXS_ASSERT(!RAM_VECTOR_TABLE_IS_CACHED, "Not implemented");
        bool ien = AreInterruptsEnabled();
        if (ien)
            DisableInterrupts();
        if (Registers::SCB::VTOR != RAM_VECTOR_TABLE) {
            Registers::SCB::VTOR = RAM_VECTOR_TABLE;
        }
        memcpy((void*)Registers::SCB::VTOR, (void*)ROM_VECTOR_TABLE, 0x200);
        ((uint32_t*)*Registers::SCB::VTOR)[offset + 16] = (uint32_t)handler;
        if (ien)
            EnableInterrupts();
    }

} // namespace CFXS::CPU