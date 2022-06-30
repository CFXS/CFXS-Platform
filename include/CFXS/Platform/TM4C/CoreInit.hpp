// [CFXS] //
#pragma once
#include <CFXS/Platform/App.hpp>

namespace CFXS::TM4C {

    struct CoreInitDescriptor {
        const size_t highPriorityTimer;   // Timer index to use for high priority
        const int splitHighPriorityTimer; // 0 == don't split, 1 == A, 2 == B
    };

} // namespace CFXS::TM4C