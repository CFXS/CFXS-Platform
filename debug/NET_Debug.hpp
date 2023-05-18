#pragma once
#include <CFXS/Base/Debug.hpp>

namespace CFXS::Debug::Network {
#ifdef RELEASE_FAST
    static constexpr CFXS::DebugLevel_t DEBUG_LEVEL = CFXS::DebugLevel::OFF;
#else
    static constexpr CFXS::DebugLevel_t DEBUG_LEVEL = CFXS::DebugLevel::SPAM;
#endif
} // namespace CFXS::Debug::Network

#define NET_CFXS_printf(level, ...)                   \
    if (level >= CFXS::Debug::Network::DEBUG_LEVEL) { \
        CFXS_printf("NET> " __VA_ARGS__);             \
    }
