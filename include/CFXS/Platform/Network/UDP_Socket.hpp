#pragma once
#include <CFXS/Base/IPv4.hpp>
#include <CFXS/Base/NetworkPacket.hpp>

struct udp_pcb;
struct pbuf;
struct ip4_addr;

namespace CFXS::Network {

    class UDP_Socket {
    public:
        UDP_Socket(const IPv4 &ip, uint16_t port);
        ~UDP_Socket();

        bool SendPacket(const NetworkPacket &packet);

    private:
        static void Process_Receive(void *arg, udp_pcb *pcb, pbuf *p, const ip4_addr *addr, uint16_t port);

    private:
        udp_pcb *m_Socket;
    };

} // namespace CFXS::Network