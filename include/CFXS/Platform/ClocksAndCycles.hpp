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

namespace CFXS::CPU {

    static constexpr size_t CLOCK_FREQUENCY = CFXS_CPU_CLOCK_FREQUENCY;

    template<typename T>
    static constexpr T GetCyclesPerSecond() {
        return CLOCK_FREQUENCY;
    };

    static constexpr size_t GetCyclesPerSecond() {
        return GetCyclesPerSecond<size_t>();
    };

    template<typename T>
    static constexpr T GetCyclesPerMillisecond() {
        return CLOCK_FREQUENCY / static_cast<T>(1000);
    };

    static constexpr size_t GetCyclesPerMillisecond() {
        return GetCyclesPerMillisecond<size_t>();
    };

    template<typename T>
    static constexpr T GetCyclesPerMicrosecond() {
        return CLOCK_FREQUENCY / static_cast<T>(1000000);
    };

    static constexpr size_t GetCyclesPerMicrosecond() {
        return GetCyclesPerMicrosecond<size_t>();
    };

} // namespace CFXS::CPU