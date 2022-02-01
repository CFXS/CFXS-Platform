// [CFXS] //
#pragma once

namespace CFXS::CPU {

    static constexpr size_t CLOCK_FREQUENCY      = CFXS_CPU_CLOCK_FREQUENCY;
    static constexpr size_t CYCLES_PER_MS        = CLOCK_FREQUENCY / 1000;
    static constexpr size_t CYCLES_PER_USEC      = CLOCK_FREQUENCY / 1000000;
    static constexpr float CYCLES_PER_MS_FLOAT   = CLOCK_FREQUENCY / 1000.0f;
    static constexpr float CYCLES_PER_USEC_FLOAT = CLOCK_FREQUENCY / 1000000.0f;

} // namespace CFXS::CPU