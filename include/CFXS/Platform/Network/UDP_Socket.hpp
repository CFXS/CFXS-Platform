#pragma once
#include <CFXS/Base/IPv4.hpp>

struct udp_pcb;
struct pbuf;
struct ip4_addr;

namespace CFXS::Network {

    class UDP_Socket {
    public:
        UDP_Socket(const CFXS::IPv4 &ip, uint16_t port);

    private:
        static void Process_Receive(void *arg, udp_pcb *pcb, pbuf *p, const ip4_addr *addr, uint16_t port);

    private:
        udp_pcb *m_Socket;
    };

} // namespace CFXS::Network