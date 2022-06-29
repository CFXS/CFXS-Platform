#pragma once
#include <CFXS/Base/Types.hpp>

namespace CFXS {

    struct AppDescriptor {
        const void* platformInitDescriptor;      // Platform specific descriptor struct
        const VoidFunction_t moduleInit;         // Call module initializers
        const VoidFunction_t postInit;           // Core/Module init done
        const size_t highPriorityLoopPeriod;     // 0 = no high priority loop
        const size_t highPriorityLoopPriority;   // Interrupt priority of high priority loop
        const size_t systemPriorityLoopPeriod;   // 0 = no system priority loop
        const size_t systemPriorityLoopPriority; // Interrupt priority of system priority loop
    };

} // namespace CFXS

extern const CFXS::AppDescriptor e_AppDescriptor;