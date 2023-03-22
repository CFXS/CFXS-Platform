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

namespace CFXS::CPU::Types {

#pragma pack(1)

    /// DWT Control Register
    struct Reg_DWT_CTRL {
        uint8_t CYCCNTENA : 1;   // Enable cycle counter
        uint8_t POSTPRESET : 4;  // Reload value for POSTCNT
        uint8_t POSTCNT : 4;     // Post-scalar counter for CYCTAP
        uint8_t CYCTAP : 1;      // Selects a tap on the DWT_CYCCNT register [0 = bit 6, 1 = bit 10]
        uint8_t SYNCTAP : 2;     // Feeds a synchronization pulse to the ITM SYNCENA control
        uint8_t PCSAMPLEENA : 1; // Enables PC Sampling event
        uint8_t _reserved0 : 3;  // Reserved
        uint8_t EXCTRCENA : 1;   // Enables Interrupt event tracing
        uint8_t CPIEVTENA : 1;   // Enables CPI count event. Emits an event when DWT_CPICNT overflows.
        uint8_t EXCEVTENA : 1;   // Enables Interrupt overhead event. Emits an event when DWT_EXCCNT overflows.
        uint8_t SLEEPEVTENA : 1; // Enables Sleep count event. Emits an event when DWT_SLEEPCNT overflows.
        uint8_t LSUEVTENA : 1;   // Enables LSU count event. Emits an event when DWT_LSUCNT overflows.
        uint8_t FOLDEVTENA : 1;  // Enables Folded instruction count event. Emits an event when DWT_FOLDCNT overflows.
        uint8_t CYCEVTEN : 1;    // Enables Cycle count event. Emits an event when the POSTCNT counter triggers it.
        uint8_t _reserved1 : 5;  // Reserved
        uint8_t NUMCOMP : 4;     // Number of comparators field.
    };

    /// DWT Cycle Count Register
    struct Reg_DWT_CYCCNT {
        uint32_t CYCCNT : 32; // Current PC Sampler Cycle Counter count value.
    };

#pragma pack()

} // namespace CFXS::CPU::Types