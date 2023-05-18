#pragma once
#include <CFXS/Base/IPv4.hpp>

namespace CFXS::Network {

    bool JoinMulticastGroup(const IPv4& ip);
    bool LeaveMulticastGroup(const IPv4& ip);

} // namespace CFXS::Network