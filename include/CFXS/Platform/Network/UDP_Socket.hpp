#pragma once
#include <CFXS/Base/Function.hpp>
#include <CFXS/Base/IPv4.hpp>
#include <CFXS/Base/NetworkPacket.hpp>
#include <CFXS/Base/NetworkPacketRef.hpp>
#include <EASTL/vector.h>

struct udp_pcb;
struct pbuf;
struct ip4_addr;

namespace CFXS::Network {

    class UDP_Socket {
    public:
        using ReceiveCallback = CFXS::Function<void(void *, const NetworkPacketRef<IPv4> &packet)>;

    public:
        UDP_Socket() = default;
        UDP_Socket(const IPv4 &ip, uint16_t port);
        ~UDP_Socket();

        /// @brief Send UDP packet
        /// @param packet Packet to send
        /// @param send_reference Send as reference buffer or copy buffer
        /// @return true if packet sent
        bool SendPacket(const NetworkPacket &packet, bool send_reference = false);

        /// @brief Get port
        /// @return UDP port
        uint16_t GetPort() const;

        void RegisterReceiveCallback(const ReceiveCallback &cb);
        void UnregisterReceiveCallback(const ReceiveCallback &cb);

    private:
        static void Process_Receive(void *arg, udp_pcb *pcb, pbuf *p, const ip4_addr *addr, uint16_t port);

    private:
        udp_pcb *m_Socket;
        eastl::vector<ReceiveCallback> m_ReceiveCallbacks;
    };

} // namespace CFXS::Network
