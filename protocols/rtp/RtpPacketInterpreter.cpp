#include "RtpPacketInterpreter.hpp"

RtpPacketInterpreter::RtpPacketInterpreter()
{
   _packet = new RtpPacket(2048);
}

void RtpPacketInterpreter::interpret()
{
    // Simulating packet reception
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Example: Find a valid packet (replace with your own validation logic)
    Packet packet = { 0x80, 0x21, 0x00,
        0x0a }; // Example RTP header (replace as needed)

    // Check if the packet is valid (simple example, replace with actual
    // validation logic)
    if (is_valid_packet(packet)) {
        // Notify subscribers about the valid packet
        notify_subscribers(packet);
    }

    // Continue interpreting packets
    interpret();
}

IRingQueue*  RtpPacketInterpreter::packet()
{
    return _packet;
}

bool RtpPacketInterpreter::is_valid_packet(const Packet &packet) {
  // Validate packet here (e.g., check for RTP header validity)
  return packet.size() > 0; // Placeholder for actual validation
}