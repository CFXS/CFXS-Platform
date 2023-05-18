#include <CFXS/Platform/Network/Interface.hpp>
#include <lwip/igmp.h>
#include <lwip/netif.h>
#include <NET_Debug.hpp>

extern netif e_Main_Network_Interface;

namespace CFXS::Network {

    bool JoinMulticastGroup(const IPv4& ip) {
        auto res = igmp_joingroup(&e_Main_Network_Interface.ip_addr, ip.GetPointerCast<ip4_addr>());
        if (res != ERR_OK) {
            NET_CFXS_printf(DebugLevel::ERROR,
                            "Failed to join multicast group %d.%d.%d.%d (%s)\n",
                            ip[0],
                            ip[1],
                            ip[2],
                            ip[3],
                            __lwip_err_t_ToString(res));
            return false;
        }
        return true;
    }

    bool LeaveMulticastGroup(const IPv4& ip) {
        auto res = igmp_leavegroup(&e_Main_Network_Interface.ip_addr, ip.GetPointerCast<ip4_addr>());
        if (res != ERR_OK) {
            NET_CFXS_printf(DebugLevel::ERROR,
                            "Failed to leave multicast group %d.%d.%d.%d (%s)\n",
                            ip[0],
                            ip[1],
                            ip[2],
                            ip[3],
                            __lwip_err_t_ToString(res));
            return false;
        }
        return true;
    }

} // namespace CFXS::Network