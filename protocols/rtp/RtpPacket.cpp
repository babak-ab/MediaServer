#include "RtpPacket.hpp"
#include <array>
#include <boost/asio.hpp>
#include <iostream>
#include <map>
std::string get_payload_type_description(uint8_t payload_type)
{
    static const std::map<uint8_t, std::string> payload_type_map = {
        // Audio payload types
        { 0, "PCMU (G.711 μ-law)" },
        { 1, "Reserved" },
        { 2, "Reserved" },
        { 3, "GSM" },
        { 4, "G723" },
        { 5, "DVI4 (8 kHz)" },
        { 6, "DVI4 (16 kHz)" },
        { 7, "LPC" },
        { 8, "PCMA (G.711 A-law)" },
        { 9, "G722" },
        { 10, "L16 (Stereo, 44.1 kHz)" },
        { 11, "L16 (Mono, 44.1 kHz)" },
        { 12, "QCELP" },
        { 13, "CN (Comfort Noise)" },
        { 14, "MPA (MPEG-1/MPEG-2 Audio)" },
        { 15, "G728" },
        { 16, "DVI4 (11.025 kHz)" },
        { 17, "DVI4 (22.05 kHz)" },
        { 18, "G729" },
        { 19, "Reserved" },
        { 20, "Unassigned" },
        { 21, "Unassigned" },
        { 22, "Unassigned" },
        { 23, "Unassigned" },

        // Video payload types
        { 24, "Uncompressed video (RFC 4175)" },
        { 25, "CelB" },
        { 26, "JPEG" },
        { 27, "Unassigned" },
        { 28, "NV" },
        { 29, "Unassigned" },
        { 30, "Unassigned" },
        { 31, "H.261" },
        { 32, "MPV (MPEG-1/MPEG-2 Video)" },
        { 33, "MP2T (MPEG-2 Transport Stream)" },
        { 34, "H.263" },

        // Dynamic payload types
        { 96, "Dynamic / Custom Payload" },
        { 97, "Dynamic / Custom Payload" },
        { 98, "Dynamic / Custom Payload" },
        { 99, "Dynamic / Custom Payload" },
        { 100, "Dynamic / Custom Payload" },
        { 101, "Dynamic / Custom Payload (often used for telephone events)" },
        { 102, "Dynamic / Custom Payload" },
        { 103, "Dynamic / Custom Payload" },
        { 104, "Dynamic / Custom Payload" },
        { 105, "Dynamic / Custom Payload" },
        { 106, "Dynamic / Custom Payload" },
        { 107, "Dynamic / Custom Payload" },
        { 108, "Dynamic / Custom Payload" },
        { 109, "Dynamic / Custom Payload" },
        { 110, "Dynamic / Custom Payload" },
        { 111, "Dynamic / Custom Payload" },
        { 112, "Dynamic / Custom Payload" },
        { 113, "Dynamic / Custom Payload" },
        { 114, "Dynamic / Custom Payload" },
        { 115, "Dynamic / Custom Payload" },
        { 116, "Dynamic / Custom Payload" },
        { 117, "Dynamic / Custom Payload" },
        { 118, "Dynamic / Custom Payload" },
        { 119, "Dynamic / Custom Payload" },
        { 120, "Dynamic / Custom Payload" },
        { 121, "Dynamic / Custom Payload" },
        { 122, "Dynamic / Custom Payload" },
        { 123, "Dynamic / Custom Payload" },
        { 124, "Dynamic / Custom Payload" },
        { 125, "Dynamic / Custom Payload" },
        { 126, "Dynamic / Custom Payload" },
        { 127, "Dynamic / Custom Payload" }
    };

    auto it = payload_type_map.find(payload_type);
    if (it != payload_type_map.end()) {
        return it->second;
    }
    return "Unknown Payload Type";
}
RtpHeader parseRtpHeader(const std::vector<uint8_t>& data)
{
    RtpHeader header;

    // Extract the first byte and decode it into the relevant fields
    uint8_t first_byte = data[0];
    header.version = (first_byte >> 6) & 0x03; // Version (2 bits)
    header.padding = (first_byte >> 5) & 0x01; // Padding (1 bit)
    header.extension = (first_byte >> 4) & 0x01; // Extension (1 bit)
    header.csrc_count = first_byte & 0x0F; // CSRC Count (4 bits)

    // Extract the second byte for marker and payload_type
    uint8_t second_byte = data[1];
    header.marker = (second_byte >> 7) & 0x01; // Marker (1 bit)
    header.payload_type = second_byte & 0x7F; // Payload Type (7 bits)

    // Extract the sequence number (16 bits) from the next two bytes
    header.sequence_number = (data[2] << 8) | data[3];

    // Extract the timestamp (32 bits) from the next four bytes
    header.timestamp = (data[4] << 24) | (data[5] << 16) | (data[6] << 8) | data[7];

    // Extract the SSRC (32 bits) from the next four bytes
    header.ssrc = (data[8] << 24) | (data[9] << 16) | (data[10] << 8) | data[11];

    return header;
}

void RtpPacket::find_packet(const std::vector<uint8_t>& packet)
{

    std::vector<std::vector<uint8_t>> data;
    get_items(data, 1);

    if (data[0].size() < 12) {
        return;
    }

    // std::memcpy(reinterpret_cast<uint8_t*>(&header), data[0].data(), sizeof(RtpHeader));
    RtpHeader header = parseRtpHeader(data[0]);

    if (header.version != 2) {
        std::cerr << "Invalid RTP version. Expected version 2, got " << static_cast<int>(header.version) << std::endl;
        return; // Invalid version
    }

    std::cout << "RTP Header Validated: " << std::endl;
    std::cout << "  Version: " << static_cast<int>(header.version) << std::endl;
    std::cout << "  Payload Type: " << static_cast<int>(header.payload_type)
              << " (" << get_payload_type_description(header.payload_type) << ")" << std::endl;

    std::cout << "  Sequence Number: " << header.sequence_number << std::endl;
    std::cout << "  Timestamp: " << header.timestamp << std::endl;

    // if (header.extension) {
    //     // Read the extension header
    //     uint16_t extension_length = 0;
    //     get_bytes(reinterpret_cast<uint8_t*>(&extension_length), sizeof(extension_length));

    //     // The extension length is in 32-bit words, so multiply by 4 to get the byte length
    //     extension_length *= 4;

    //     std::cout << "Extension Header Found. Length: " << extension_length << " bytes." << std::endl;

    //     // Move the buffer forward by the length of the extension header
    //     if (extension_length > 0) {
    //         std::vector<uint8_t> extension_data(extension_length);
    //         get_bytes(extension_data.data(), extension_length);

    //         // Optionally, you can process the extension data here
    //         std::cout << "Processing extension data..." << std::endl;
    //         // Process extension data as needed (you can check for specific extension types)
    //     }
    // } else {
    //     std::cout << "No extension header present." << std::endl;
    // }
}