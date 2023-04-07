// [CFXS] //
#pragma once

namespace CFXS::Benchmark {

    /// @brief Measures execution time of a function
    /// @param fn function to run
    /// @return execution time in cycles
    template<typename T>
    constexpr uint64_t MeasureExecutionCycles(T&& fn) {
        volatile auto t1 = CPU::GetCycleCount();
        fn();
        volatile auto t2       = CPU::GetCycleCount();
        volatile uint64_t diff = (t2 > t1 ? (t2 - t1) : ((((uint64_t)t2) + 0xFFFFFFFF) - t1)) - 3;
        return diff;
    }

} // namespace CFXS::Benchmark