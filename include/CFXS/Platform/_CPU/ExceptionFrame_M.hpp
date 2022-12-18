#pragma once

namespace CFXS::CPU {

    struct ExceptionFrame_M {
        volatile uint32_t R0;
        volatile uint32_t R1;
        volatile uint32_t R2;
        volatile uint32_t R3;
        volatile uint32_t R12;
        volatile uint32_t LR;
        volatile uint32_t PC;
        volatile uint32_t PSR;
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

} // namespace CFXS::CPU