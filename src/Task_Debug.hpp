#pragma once
#include <CFXS/Base/Debug.hpp>

namespace CFXS {
#ifdef RELEASE_FAST
    static constexpr CFXS::DebugLevel_t TASK_DEBUG_LEVEL = CFXS::DebugLevel::OFF;
#else
    static constexpr CFXS::DebugLevel_t TASK_DEBUG_LEVEL = CFXS::DebugLevel::TRACE;
#endif
} // namespace CFXS

#define CFXS_Task_printf(level, ...)                 \
    if constexpr (level >= CFXS::TASK_DEBUG_LEVEL) { \
        CFXS_printf("Task> " __VA_ARGS__);           \
    }
