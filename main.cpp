#include "RtpPacketInterpreter.hpp"
#include "Subscriber.hpp"
#include <array>
#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::udp;

class UDPReceiver : public std::enable_shared_from_this<Subscriber> {
public:
    UDPReceiver(boost::asio::io_context& io_context, short port)
        : socket_(io_context, udp::endpoint(udp::v4(), port))
    {

        packet = std::make_shared<RtpPacketInterpreter>();
        // packet->add_subscriber(shared_from_this());
        start_receive();
    }

    void receive_notification(const std::vector<uint8_t>& message)
    {
    }

private:
    void start_receive()
    {
        socket_.async_receive_from(
            boost::asio::buffer(receive_buffer_), remote_endpoint_,
            [this](boost::system::error_code ec, std::size_t bytes_received) {
                if (!ec) {
                    //std::cout << "Received: " << bytes_received << " bytes" << std::endl;

                    std::vector<uint8_t> byteVector(receive_buffer_.begin(), receive_buffer_.begin() + bytes_received);

                    packet->append(byteVector);

                    // Print the first 4 bytes as hex
                    // std::cout << "First 4 bytes (Hex): ";
                    // for (size_t i = 0; i < 30 && i < bytes_received; ++i) {
                    //     std::cout << std::hex << std::setw(2) << std::setfill('0')
                    //               << (static_cast<int>(receive_buffer_[i]) & 0xFF) << " ";
                    // }
                    // std::cout << std::dec << std::endl; // Switch back to decimal output

                } else {
                    std::cout << "Error receiving message: " << ec.message() << std::endl;
                }

                // Continue receiving
                start_receive();
            });
    }

    udp::socket socket_;
    udp::endpoint remote_endpoint_;
    std::array<char, 1024> receive_buffer_;
    std::shared_ptr<RtpPacketInterpreter> packet;
};

int main()
{
    try {
        boost::asio::io_context io_context;
        UDPReceiver receiver(io_context, 5001); // Listen on port 12345
        io_context.run(); // Start the asynchronous I/O
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
