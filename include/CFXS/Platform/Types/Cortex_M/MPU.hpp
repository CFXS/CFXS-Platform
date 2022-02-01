// [CFXS] //
#pragma once

namespace CFXS::CPU::Types {

#pragma pack(1)

    /// MPU Type Register
    struct Reg_MPU_TYPE {
        uint8_t SEPERATE : 1;   // Unified or separate instruction and date memory maps
        uint8_t _reserved0 : 7; // Reserved
        uint8_t DREGION : 8;    // Number of supported MPU data regions
        uint8_t IREGION : 8;    // Number of supported MPU instruction regions
        uint8_t _reserved1 : 8; // Reserved
    };

    /// MPU Control Register
    struct Reg_MPU_CTRL {
        uint8_t ENABLE : 1;       // MPU enable/disable
        uint8_t HFNMIENA : 1;     // Enable the operation of MPU during hard fault, NMI, and FAULTMASK handlers
        uint8_t PRIVDEFENA : 1;   // Enable privileged software access to the default memory map
        uint32_t _reserved0 : 29; // Reserved
    };

    /// MPU Region Number Register
    struct Reg_MPU_RNR {
        uint8_t REGION : 8;       // MPU region referenced by the MPU_RBAR and MPU_RASR registers
        uint32_t _reserved0 : 24; // Reserved
    };

    /// MPU Region Base Address Register
    struct Reg_MPU_RBAR {};

    /// MPU Region Attribute and Size Register
    struct Reg_MPU_RASR {};

#pragma pack()

} // namespace CFXS::CPU::Types