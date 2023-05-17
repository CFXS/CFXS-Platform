#pragma once
#include <CFXS/Base/Debug.hpp>

namespace CFXS {
    static constexpr CFXS::DebugLevel_t TASK_DEBUG_LEVEL = CFXS::DebugLevel::TRACE;
}

#define CFXS_Task_printf(level, ...)                 \
    if constexpr (level >= CFXS::TASK_DEBUG_LEVEL) { \
        CFXS_printf("Task> " __VA_ARGS__);           \
    }
