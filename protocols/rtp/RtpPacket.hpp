
#pragma once
#include "RingQueue.hpp"
#include <cstring> // For memcpy
#include <vector>

struct RtpHeader {
    uint8_t version : 2; // 2 bits for version
    uint8_t padding : 1; // 1 bit for padding
    uint8_t extension : 1; // 1 bit for extension
    uint8_t csrc_count : 4; // 4 bits for CSRC count
    uint8_t marker : 1; // 1 bit for marker
    uint8_t payload_type : 7; // 7 bits for payload type
    uint16_t sequence_number; // 16 bits for sequence number
    uint32_t timestamp; // 32 bits for timestamp
    uint32_t ssrc; // 32 bits for SSRC
};
class RtpPacket : public IRingQueue {
public:
    explicit RtpPacket()
        : IRingQueue()
    {
    }

    void find_packet(const std::vector<uint8_t>& packet) override;

private:
};