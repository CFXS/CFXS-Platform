#pragma once

namespace CFXS::CPU::ARMv7_M {

    struct ExceptionReturn {
        bool ES : 1;         // [ARMv8] Secure mode
        bool _reserved0 : 1; //
        bool SPSEL : 1;      // [ARMv7] (0 == MSP, 1 == PSP)
        bool MODE : 1;       // [ARMv7] (0 == handler mode, 1 == thread mode)
        bool FTYPE : 1;      // [ARMv7] Frame type (0 == extended, 1 == normal)
        bool DCRS : 1;       // [ARMv8] Default callee register stacking
        bool S : 1;          // [ARMv8] Secure stack entry
        uint32_t _reserved1 : 17;
        uint8_t _ff;
    };

    struct ExceptionFrame {
        volatile uint32_t R0;
        volatile uint32_t R1;
        volatile uint32_t R2;
        volatile uint32_t R3;
        volatile uint32_t R12;
        volatile uint32_t LR;
        volatile uint32_t ReturnAddress;
        volatile uint32_t xPSR;
    };

    struct ExtendedExceptionFrame {
        volatile uint32_t R0;
        volatile uint32_t R1;
        volatile uint32_t R2;
        volatile uint32_t R3;
        volatile uint32_t R12;
        volatile uint32_t LR;
        volatile uint32_t ReturnAddress;
        volatile uint32_t xPSR;
        volatile uint32_t S0;
        volatile uint32_t S1;
        volatile uint32_t S2;
        volatile uint32_t S3;
        volatile uint32_t S4;
        volatile uint32_t S5;
        volatile uint32_t S6;
        volatile uint32_t S7;
        volatile uint32_t S8;
        volatile uint32_t S9;
        volatile uint32_t S10;
        volatile uint32_t S11;
        volatile uint32_t S12;
        volatile uint32_t S13;
        volatile uint32_t S14;
        volatile uint32_t S15;
        volatile uint32_t FPSCR;
    };

    struct BusFaultStatusRegister {
        bool IBUSERR : 1;
        bool PRECISERR : 1;
        bool IMPRECISERR : 1;
        bool UNSTKERR : 1;
        bool STKERR : 1;
        bool LSPERR : 1;
        bool _reserved1 : 1;
        bool BFARVALID : 1;
    };

    struct MemManageFaultStatusRegister {
        bool IACCVIOL : 1;
        bool DACCVIOL : 1;
        bool _reserved0 : 1;
        bool MUNSTKERR : 1;
        bool MSTKERR : 1;
        bool MLSPERR : 1;
        bool _reserved2 : 1;
        bool MMARVALID : 1;
    };

    struct UsageFaultStatusRegister {
        bool UNDEFINSTR : 1;
        bool INVSTATE : 1;
        bool INVPC : 1;
        bool NOCP : 1;
        uint8_t _reserved1 : 4;
        bool UNALIGNED : 1;
        bool DIVBYZERO : 1;
        uint8_t _reserved0 : 6;
    };

} // namespace CFXS::CPU::ARMv7_M