#ifndef EF24F8E0_17B3_486F_8ECC_C96989993317
#define EF24F8E0_17B3_486F_8ECC_C96989993317

#include "PacketInterpreter.hpp"
#include <RtpPacket.hpp>
class RtpPacketInterpreter : public PacketInterpreter {
public:
    RtpPacketInterpreter();
    void interpret() override;

    IRingQueue* packet() override;

private:
    bool is_valid_packet(const Packet& packet);
    RtpPacket* _packet;
};

#endif /* EF24F8E0_17B3_486F_8ECC_C96989993317 */
