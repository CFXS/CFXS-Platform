// [CFXS] //
#pragma once

namespace CFXS::CPU {

    static constexpr size_t CLOCK_FREQUENCY = CFXS_CPU_CLOCK_FREQUENCY;

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