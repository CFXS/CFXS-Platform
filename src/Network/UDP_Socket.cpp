#include <CFXS/Platform/Network/UDP_Socket.hpp>
#include <lwip/udp.h>

namespace CFXS::Network {

    UDP_Socket::UDP_Socket(const IPv4 &ip, uint16_t port) {
        m_Socket = udp_new();
        udp_recv(m_Socket, Process_Receive, this);
        udp_bind(m_Socket, ip.GetPointerCast<ip4_addr>(), port);
        ip_set_option(m_Socket, SOF_REUSEADDR | SOF_BROADCAST);
        m_Socket->netif_idx     = 0;
        m_Socket->mcast_ifindex = 0;
    }

    UDP_Socket::~UDP_Socket() {
        udp_remove(m_Socket);
    }

    bool UDP_Socket::SendPacket(const NetworkPacket &packet) {
        auto packet_buffer = pbuf_alloc_reference((void *)packet.GetData(), packet.GetSize(), PBUF_REF);

        if (!packet_buffer) {
            return false;
        }

        auto res =
            udp_sendto(m_Socket, packet_buffer, packet.GetDestinationAddress().GetPointerCast<ip4_addr>(), packet.GetDestinationPort());

        if (res != ERR_OK) {
            pbuf_free(packet_buffer);
            // CFXS_printf("UDP send error [%s] dest %u.%u.%u.%u:%u\n",
            //             __lwip_err_t_ToString(res),
            //             packet.GetDestinationAddress()[0],
            //             packet.GetDestinationAddress()[1],
            //             packet.GetDestinationAddress()[2],
            //             packet.GetDestinationAddress()[3],
            //             packet.GetDestinationPort());
            return false;
        }

        pbuf_free(packet_buffer);
        return true;
    }

    void UDP_Socket::Process_Receive(void *arg, udp_pcb *pcb, pbuf *p, const ip4_addr *addr, uint16_t port) {
        char addr_str[32];
        CFXS::IPv4{addr->addr}.PrintTo(addr_str, 32);
        CFXS_printf("UDP received %d bytes from %s:%u\n", p->tot_len, addr_str, port);
        pbuf_free(p);
    }

} // namespace CFXS::Network