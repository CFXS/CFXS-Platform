// [CFXS] //
#include "../../Types/Cortex_M/MPU.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"

namespace CFXS::CPU::Registers {

    namespace MPU {

        static auto* MPU_TYPE = reinterpret_cast<const volatile Types::Reg_MPU_TYPE*>(0xE000ED90);
        static auto* MPU_CTRL = reinterpret_cast<volatile Types::Reg_MPU_CTRL*>(0xE000ED94);
        static auto* MPU_RNR  = reinterpret_cast<volatile Types::Reg_MPU_RNR*>(0xE000ED98);
        static auto* MPU_RBAR = reinterpret_cast<volatile Types::Reg_MPU_RBAR*>(0xE000ED9C);
        static auto* MPU_RASR = reinterpret_cast<volatile Types::Reg_MPU_RASR*>(0xE000EDA0);

    } // namespace MPU

} // namespace CFXS::CPU::Registers

#pragma GCC diagnostic pop