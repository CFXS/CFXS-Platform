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
#include <CFXS/Base/Types.hpp>

namespace CFXS {

    struct AppDescriptor {
        const void* platformInitDescriptor;      // Platform specific descriptor struct
        const VoidFunction_t moduleInit;         // Call module initializers
        const VoidFunction_t postModuleInit;     // Core/Module init done
        const size_t highPriorityLoopPeriod;     // 0 = no high priority loop
        const size_t highPriorityLoopPriority;   // Interrupt priority of high priority loop
        const size_t systemPriorityLoopPeriod;   // 0 = no system priority loop
        const size_t systemPriorityLoopPriority; // Interrupt priority of system priority loop
    };

} // namespace CFXS

extern const CFXS::AppDescriptor e_AppDescriptor;