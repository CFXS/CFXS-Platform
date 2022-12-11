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
#include <CFXS/Base/Debug.hpp>
#include <CFXS/Base/Utility.hpp>
#include <CFXS/Platform/App.hpp>
#include <CFXS/Platform/STM32/CoreInit.hpp>
#include <CFXS/Platform/CPU.hpp>

extern void CFXS_SystemPriorityLoop();
extern void CFXS_HighPriorityLoop();

namespace CFXS::Platform {

    void CoreInit(const AppDescriptor &appDesc) {
        CFXS_ASSERT(appDesc.platformInitDescriptor, "Platform init descriptor is null");
        if (appDesc.platformInitDescriptor) {
            auto &platformDesc = *static_cast<const STM32::CoreInitDescriptor *>(appDesc.platformInitDescriptor);
            CFXS::SafeCall(platformDesc.systemInit);
        }

        if (appDesc.systemPriorityLoopPeriod) {
            CFXS_ASSERT(appDesc.systemPriorityLoopPeriod <= 16777216, "Invalid SysTick period");
            // CFXS::CPU::SetInterruptHandler(-1, CFXS_SystemPriorityLoop);
            __mem32(0xE000E014) = appDesc.systemPriorityLoopPeriod - 1; // Set period
            __mem32(0xE000E010) = 0x04 | 0x02 | 0x01;                   // Enable clock source + interrupt + enable systick
        }

        if (appDesc.highPriorityLoopPeriod) {
        }
    }

} // namespace CFXS::Platform