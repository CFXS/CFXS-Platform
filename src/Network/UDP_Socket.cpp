#include <CFXS/Platform/Network/UDP_Socket.hpp>
#include <lwip/udp.h>

namespace CFXS::Network {

    UDP_Socket::UDP_Socket(const CFXS::IPv4 &ip, uint16_t port) {
        m_Socket = udp_new();
        udp_recv(m_Socket, Process_Receive, this);
        ip4_addr addr;
        addr.addr = ip.ToNetworkOrder();
        udp_bind(m_Socket, &addr, port);
        ip_set_option(m_Socket, SOF_REUSEADDR | SOF_BROADCAST);
    }

    void UDP_Socket::Process_Receive(void *arg, udp_pcb *pcb, pbuf *p, const ip4_addr *addr, uint16_t port) {
        char addr_str[32];
        CFXS::IPv4{addr->addr}.PrintTo(addr_str, 32);
        CFXS_printf("UDP received %d bytes from %s:%u\n", p->tot_len, addr_str, port);
        pbuf_free(p);
    }

} // namespace CFXS::Network