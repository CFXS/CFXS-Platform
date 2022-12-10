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
#include <CFXS/Platform/App.hpp>
#include <CFXS/Platform/STM32/CoreInit.hpp>

extern void CFXS_SystemPriorityLoop();
extern void CFXS_HighPriorityLoop();

namespace CFXS::Platform {

    void CoreInit(const AppDescriptor &appDesc) {
        // auto &platformDesc = *static_cast<const STM32::CoreInitDescriptor *>(appDesc.platformInitDescriptor);

        if (appDesc.systemPriorityLoopPeriod) {
            // SysTickIntRegister(CFXS_SystemPriorityLoop);
            // SysTickPeriodSet(appDesc.systemPriorityLoopPeriod);
            // SysTickIntEnable();
            // SysTickEnable();
        }

        if (appDesc.highPriorityLoopPeriod) {
        }
    }

} // namespace CFXS::Platform