#pragma one
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#include "RingQueue.hpp"
#include "Publisher.hpp"

class PacketInterpreter : public Publisher {
public:
    using Packet = std::vector<uint8_t>; // Example packet type, adjust as needed

    void append(const std::vector<uint8_t>& packet);

    PacketInterpreter();
    virtual ~PacketInterpreter() = default;

    void start();
    void join();

protected:
    // Pure virtual function to be implemented by subclasses to process the packet
    // data
    virtual void interpret() = 0;
    virtual std::shared_ptr<IRingQueue> packet() = 0;

    std::mutex mutex_; // Mutex to protect subscriber list

    std::thread thread_;

    // Interpreter thread
};