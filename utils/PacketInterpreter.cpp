#include "PacketInterpreter.hpp"

void PacketInterpreter::append(const std::vector<uint8_t>& message)
{
  packet()->append(message.data(),message.size());
}

// Start the interpreter thread
void PacketInterpreter::start() {
  thread_ = std::thread(&PacketInterpreter::interpret, this);
}

// Join the interpreter thread
void PacketInterpreter::join() {
  if (thread_.joinable()) {
    thread_.join();
  }
}
