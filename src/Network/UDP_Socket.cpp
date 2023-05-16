#include <CFXS/Platform/Network/UDP_Socket.hpp>
#include <CFXS/Platform/CPU.hpp>
#include <lwip/udp.h>
#include <lwip/netif.h>
#include <lwip/ip.h>

extern netif e_Main_Network_Interface;
extern ip_globals ip_data;

namespace CFXS::Network {

    UDP_Socket::UDP_Socket(const IPv4 &ip, uint16_t port) {
        m_Socket = udp_new();
        udp_recv(m_Socket, Process_Receive, this);
        udp_bind(m_Socket, ip.GetPointerCast<ip4_addr>(), port);
        ip_set_option(m_Socket, SOF_REUSEADDR | SOF_BROADCAST);
    }

    UDP_Socket::~UDP_Socket() {
        udp_remove(m_Socket);
    }

    bool UDP_Socket::SendPacket(const NetworkPacket &packet, bool send_reference) {
        // pbuf_alloc_reference is not faster than pbuf_alloc with copy???

        if (!e_Main_Network_Interface._.link) { // link down
            return false;
        }

        pbuf *packet_buffer;

        if (send_reference) {
            packet_buffer = pbuf_alloc_reference((void *)packet.GetData(), packet.GetSize(), PBUF_REF);
        } else {
            packet_buffer = pbuf_alloc_and_take(PBUF_TRANSPORT, packet.GetDataCast<void>(), packet.GetSize(), PBUF_RAM);
        }

        if (!packet_buffer) {
            return false;
        }

        auto res =
            udp_sendto(m_Socket, packet_buffer, packet.GetDestinationAddress().GetPointerCast<ip4_addr>(), packet.GetDestinationPort());

        if (res != ERR_OK) {
            pbuf_free(packet_buffer);
            CFXS_printf("UDP TX error [%s]", __lwip_err_t_ToString(res));

            if (res == ERR_RTE) {
                CFXS_printf(" -> %u.%u.%u.%u:%u\n",
                            packet.GetDestinationAddress()[0],
                            packet.GetDestinationAddress()[1],
                            packet.GetDestinationAddress()[2],
                            packet.GetDestinationAddress()[3],
                            packet.GetDestinationPort());
            } else {
                CFXS_printf("\n");
            }
            return false;
        }

        pbuf_free(packet_buffer);
        return true;
    }

    uint16_t UDP_Socket::GetPort() const {
        return m_Socket->local_port;
    }

    void UDP_Socket::RegisterReceiveCallback(const ReceiveCallback &cb) {
        CFXS::CPU::NoInterruptScope _;
        m_ReceiveCallbacks.push_back(cb);
    }

    void UDP_Socket::UnregisterReceiveCallback(const ReceiveCallback &unreg_cb) {
        CFXS::CPU::NoInterruptScope _;
        eastl::erase_if(m_ReceiveCallbacks, [&](const ReceiveCallback &cb) {
            return cb.GetFunctionPointer() == unreg_cb.GetFunctionPointer();
        });
    }

    void UDP_Socket::Process_Receive(void *arg, udp_pcb *pcb, pbuf *p, const ip4_addr *addr, uint16_t port) {
        UDP_Socket *socket = reinterpret_cast<UDP_Socket *>(arg);
        NetworkPacketRef<IPv4> packet(p, IPv4{addr->addr}, port, IPv4{ip_data.current_iphdr_src.addr}, socket->GetPort());

        for (auto &cb : socket->m_ReceiveCallbacks)
            cb(packet);

        pbuf_free(p);
    }

} // namespace CFXS::Network