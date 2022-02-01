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
    struct Reg_MPU_RBAR {
        uint32_t ADDR : 27; // Variable size based on RASR size
        uint8_t VALID : 1;  // Reads as 0 (write 0 = REGION field ignored, RNR used; write 1 = REGION field used, RNR ignored)
        uint8_t REGION : 4; // MPU region (reads current region specified by RNR)

        inline void SetAddress(uint32_t regionSizeLog2, uint32_t addr) {
            ADDR = addr << (regionSizeLog2 - 4);
        }

        inline void SetAddress(uint32_t regionSizeLog2, uint32_t addr, uint8_t region) {
            REGION = region;
            ADDR   = addr << (regionSizeLog2 - 4);
        }
    };

    /// MPU Region Attribute and Size Register
    struct Reg_MPU_RASR {
        uint8_t ENABLE : 1;     // Region enable/disable
        uint8_t SIZE : 5;       // Size of this region
        uint8_t _reserved0 : 2; // Reserved
        uint8_t SRD : 8;        // Subregion disable bits
        uint8_t B : 1;
        uint8_t C : 1;
        uint8_t S : 1; // Shareable
        uint8_t TEX : 3;
        uint8_t _reserved1 : 2; // Reserved
        uint8_t AP : 3;         // Access permissions
        uint8_t _reserved2 : 1; // Reserved
        uint8_t XN : 1;         // Instruction access enable/disable
        uint8_t _reserved3 : 3; // Reserved
    };

#pragma pack()

} // namespace CFXS::CPU::Types