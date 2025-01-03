#include "RtpPacket.hpp"

void RtpPacket::read_at_offset(uint8_t* dest, size_t length, size_t offset)
{
    for (size_t i = 0; i < length; ++i) {
        size_t index = (head_ + offset + i) % buffer_.size();
        dest[i] = buffer_[index];
    }
}

bool RtpPacket::find_packet()
{
    if (size_ < sizeof(RtpHeader)) {
        return false; // Not enough data to form a valid RTP header
    }

    // Check if we have a valid RTP packet by parsing the header
    RtpHeader header;
    read_at_offset(reinterpret_cast<uint8_t*>(&header), sizeof(header), 0);

    if (header.version == 2) { // RTP version should be 2
        std::cout << "Valid RTP packet found!" << std::endl;
        std::cout << "Sequence Number: " << header.sequence_number << std::endl;
        std::cout << "Timestamp: " << header.timestamp << std::endl;

        // Consume the header from the buffer
        uint8_t temp[sizeof(RtpHeader)];
        get_bytes(temp, sizeof(RtpHeader));

        return true;
    }

    return false; // Invalid RTP header
}