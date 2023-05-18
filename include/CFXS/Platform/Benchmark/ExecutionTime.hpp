// [CFXS] //
#pragma once
#include <CFXS/Platform/CPU.hpp>

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

    class ScopeExecutionTimePrinter {
    public:
        ScopeExecutionTimePrinter(const char* label) : m_Start(CPU::GetCycleCount()), m_Label(label) {
        }
        ~ScopeExecutionTimePrinter() {
            volatile auto t2       = CPU::GetCycleCount();
            volatile uint64_t diff = (t2 > m_Start ? (t2 - m_Start) : ((((uint64_t)t2) + 0xFFFFFFFF) - m_Start)) - 3;
            printf("[Exec \"%s\"] %lluus\n", m_Label, diff / CPU::GetCyclesPerMicrosecond());
        }

    private:
        volatile uint32_t m_Start;
        const char* m_Label;
    };

} // namespace CFXS::Benchmark