// [CFXS] //
#pragma once

#include <CFXS/Platform/CPU.hpp>
#include <CFXS/Platform/Benchmark/ExecutionTime.hpp>

namespace CFXS::Benchmark {

    class MemorySpeed {
    public:
        static void RunTest(uint8_t* region, size_t region_size, size_t reps, bool read_only) {
            if (region_size & 7) {
                CFXS_ASSERT(0, "size not aligned to 8\n");
                return;
            }

            CPU::NoInterruptScope _;
            volatile uint8_t tmp_8   = 0;
            volatile uint16_t tmp_16 = 0;
            volatile uint32_t tmp_32 = 0;
            volatile uint64_t tmp_64 = 0;

            auto exec_time_memset = read_only ? 0 : MeasureExecutionCycles([=]() {
                for (auto r = 0; r < reps; r++) {
                    memset(region, r, region_size);
                }
            });

            auto copy_size        = region_size / 2;
            auto copy_src         = region;
            auto copy_dest        = region + copy_size;
            auto exec_time_memcpy = read_only ? 0 : MeasureExecutionCycles([=]() {
                for (auto r = 0; r < reps; r++) {
                    memcpy(copy_src, copy_dest, copy_size);
                }
            });

            auto size             = region_size;
            auto exec_time_8_read = MeasureExecutionCycles([&]() {
                for (auto r = 0; r < reps; r++) {
                    size      = region_size;
                    auto rptr = (uint8_t*)region;
                    while (size--) {
                        tmp_8 = *rptr++;
                    }
                }
            });

            auto exec_time_16_read = MeasureExecutionCycles([&]() {
                for (auto r = 0; r < reps; r++) {
                    size      = region_size;
                    auto rptr = (uint16_t*)region;
                    while (size -= 2) {
                        tmp_16 = *rptr++;
                    }
                }
            });

            auto exec_time_32_read = MeasureExecutionCycles([&]() {
                for (auto r = 0; r < reps; r++) {
                    size      = region_size;
                    auto rptr = (uint32_t*)region;
                    while (size -= 4) {
                        tmp_32 = *rptr++;
                    }
                }
            });

            auto exec_time_64_read = MeasureExecutionCycles([&]() {
                for (auto r = 0; r < reps; r++) {
                    size      = region_size;
                    auto rptr = (uint64_t*)region;
                    while (size -= 8) {
                        tmp_64 = *rptr++;
                    }
                }
            });

            auto exec_time_8_write = read_only ? 0 : MeasureExecutionCycles([&]() {
                for (auto r = 0; r < reps; r++) {
                    size      = region_size;
                    auto wptr = (uint8_t*)region;
                    while (size--) {
                        *wptr++ = tmp_8;
                    }
                }
            });

            auto exec_time_16_write = read_only ? 0 : MeasureExecutionCycles([&]() {
                for (auto r = 0; r < reps; r++) {
                    size      = region_size;
                    auto wptr = (uint16_t*)region;
                    while (size -= 2) {
                        *wptr++ = tmp_16;
                    }
                }
            });

            auto exec_time_32_write = read_only ? 0 : MeasureExecutionCycles([&]() {
                for (auto r = 0; r < reps; r++) {
                    size      = region_size;
                    auto wptr = (uint32_t*)region;
                    while (size -= 4) {
                        *wptr++ = tmp_32;
                    }
                }
            });

            auto exec_time_64_write = read_only ? 0 : MeasureExecutionCycles([&]() {
                for (auto r = 0; r < reps; r++) {
                    size      = region_size;
                    auto wptr = (uint64_t*)region;
                    while (size -= 8) {
                        *wptr++ = tmp_64;
                    }
                }
            });

            float rate_memset = (float)region_size / (((float)exec_time_memset / CPU::GetCyclesPerSecond<float>()) / (float)reps);
            float rate_memcpy = (float)region_size / (((float)exec_time_memcpy / CPU::GetCyclesPerSecond<float>()) / (float)reps);

            float rate_read_8  = (float)region_size / (((float)exec_time_8_read / CPU::GetCyclesPerSecond<float>()) / (float)reps);
            float rate_read_16 = (float)region_size / (((float)exec_time_16_read / CPU::GetCyclesPerSecond<float>()) / (float)reps);
            float rate_read_32 = (float)region_size / (((float)exec_time_32_read / CPU::GetCyclesPerSecond<float>()) / (float)reps);
            float rate_read_64 = (float)region_size / (((float)exec_time_64_read / CPU::GetCyclesPerSecond<float>()) / (float)reps);

            float rate_write_8  = (float)region_size / (((float)exec_time_8_write / CPU::GetCyclesPerSecond<float>()) / (float)reps);
            float rate_write_16 = (float)region_size / (((float)exec_time_16_write / CPU::GetCyclesPerSecond<float>()) / (float)reps);
            float rate_write_32 = (float)region_size / (((float)exec_time_32_write / CPU::GetCyclesPerSecond<float>()) / (float)reps);
            float rate_write_64 = (float)region_size / (((float)exec_time_64_write / CPU::GetCyclesPerSecond<float>()) / (float)reps);

            CFXS_printf("[CFXS::Benchmark::MemorySpeed] Test %u bytes %u time%s | R%s | MB/s\n",
                        region_size,
                        reps,
                        reps == 1 ? "" : "s",
                        read_only ? "" : "/W");
            CFXS_printf("> Test 0x%08lX - 0x%08lX\n", (uint32_t)region, (uint32_t)region + size - 1);
            if (!read_only) {
                CFXS_printf("> Range\n");
                CFXS_printf("  - memset:   %.3f\n", rate_memset / 1024.0f / 1024.0f);
                CFXS_printf("  - memcpy:   %.3f\n", rate_memcpy / 1024.0f / 1024.0f);
            }
            CFXS_printf("> Single Read\n");
            CFXS_printf("  - uint8_t:  %.3f\n", rate_read_8 / 1024.0f / 1024.0f);
            CFXS_printf("  - uint16_t: %.3f\n", rate_read_16 / 1024.0f / 1024.0f);
            CFXS_printf("  - uint32_t: %.3f\n", rate_read_32 / 1024.0f / 1024.0f);
            CFXS_printf("  - uint64_t: %.3f\n", rate_read_64 / 1024.0f / 1024.0f);
            if (!read_only) {
                CFXS_printf("> Single Write\n");
                CFXS_printf("  - uint8_t:  %.3f\n", rate_write_8 / 1024.0f / 1024.0f);
                CFXS_printf("  - uint16_t: %.3f\n", rate_write_16 / 1024.0f / 1024.0f);
                CFXS_printf("  - uint32_t: %.3f\n", rate_write_32 / 1024.0f / 1024.0f);
                CFXS_printf("  - uint64_t: %.3f\n", rate_write_64 / 1024.0f / 1024.0f);
            }
        };
    };

}; // namespace CFXS::Benchmark