#include "RtpPacketInterpreter.hpp"

RtpPacketInterpreter::RtpPacketInterpreter()
{
    _packet = std::make_shared<RtpPacket>();
}

void RtpPacketInterpreter::interpret()
{
    // Simulating packet reception
    std::this_thread::sleep_for(std::chrono::milliseconds(1));


   
    // Example: Find a valid packet (replace with your own validation logic)
    Packet packet;
    _packet->find_packet(packet);
    // Check if the packet is valid (simple example, replace with actual
    // validation logic)
    // if (is_valid_packet(packet)) {
    //     // Notify subscribers about the valid packet
    //     notify_subscribers(packet);
    // }

    // Continue interpreting packets
    interpret();
}

std::shared_ptr<IRingQueue<std::vector<uint8_t>>> RtpPacketInterpreter::packet()
{
    return _packet;
}

bool RtpPacketInterpreter::is_valid_packet(const Packet& packet)
{
    // Validate packet here (e.g., check for RTP header validity)
    return packet.size() > 0; // Placeholder for actual validation
}