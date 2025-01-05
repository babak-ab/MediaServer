#ifndef EF24F8E0_17B3_486F_8ECC_C96989993317
#define EF24F8E0_17B3_486F_8ECC_C96989993317

#include "PacketInterpreter.hpp"
#include <RtpPacket.hpp>
class RtpPacketInterpreter : public PacketInterpreter {
public:
    RtpPacketInterpreter();
    void interpret() override;

    std::shared_ptr<IRingQueue<std::vector<uint8_t>>> packet() override;

private:
    bool is_valid_packet(const Packet& packet);
    std::shared_ptr<RtpPacket> _packet;
};

#endif /* EF24F8E0_17B3_486F_8ECC_C96989993317 */
