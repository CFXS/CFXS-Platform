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
#include "../../Types/Cortex_M/MPU.hpp"
#include "../../Types/Cortex_M/DWT.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"

namespace CFXS::CPU::Registers {

    namespace SCB {
        static auto* VTOR = reinterpret_cast<__rw size_t*>(0xE000ED08);
    }

    namespace MPU {

        static auto* MPU_TYPE = reinterpret_cast<__ro Types::Reg_MPU_TYPE*>(0xE000ED90);
        static auto* MPU_CTRL = reinterpret_cast<__rw Types::Reg_MPU_CTRL*>(0xE000ED94);
        static auto* MPU_RNR  = reinterpret_cast<__rw Types::Reg_MPU_RNR*>(0xE000ED98);
        static auto* MPU_RBAR = reinterpret_cast<__rw Types::Reg_MPU_RBAR*>(0xE000ED9C);
        static auto* MPU_RASR = reinterpret_cast<__rw Types::Reg_MPU_RASR*>(0xE000EDA0);

    } // namespace MPU

    namespace DWT {

        static auto* DWT_CTRL   = reinterpret_cast<__rw Types::Reg_DWT_CTRL*>(0xE0001000);
        static auto* DWT_CYCCNT = reinterpret_cast<__rw Types::Reg_DWT_CYCCNT*>(0xE0001004);

    } // namespace DWT

} // namespace CFXS::CPU::Registers

#pragma GCC diagnostic pop