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
#include "ClocksAndCycles.hpp"

#if defined(CFXS_PLATFORM_TM4C)
    #include "_CPU/TM4C.hpp"
#elif defined(CFXS_PLATFORM_STM32)
    #if defined(CFXS_DEVICE_CLASS_STM32H7x3)
        #include "_CPU/STM32H7.hpp"
    #else
        #error CFXS_DEVICE_CLASS_ not defined
    #endif
#else
    #error CFXS_PLATFORM_ not defined
#endif

namespace CFXS::CPU {

    template<typename T>
    inline void SafeExec(T&& fn) {
        bool ien = AreInterruptsEnabled();
        if (ien)
            DisableInterrupts();
        fn();
        if (ien)
            EnableInterrupts();
    }

} // namespace CFXS::CPU