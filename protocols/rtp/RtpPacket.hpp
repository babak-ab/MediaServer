
#pragma once
#include <cstring> // For memcpy
#include "RingQueue.hpp"

struct RtpHeader {
    uint8_t version : 2;
    uint8_t padding : 1;
    uint8_t extension : 1;
    uint8_t csrc_count : 4;
    uint8_t marker : 1;
    uint8_t payload_type : 7;
    uint16_t sequence_number;
    uint32_t timestamp;
    uint32_t ssrc;
};
class RtpPacket : public IRingQueue {
public:
    explicit RtpPacket(size_t capacity)
        : IRingQueue(capacity)
    {
    }

    bool find_packet() override;

private:
    // Read data at a specific offset in the buffer

    void read_at_offset(uint8_t* dest, size_t length, size_t offset);
};