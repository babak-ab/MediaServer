// Subscriber.hpp
#pragma once
#include <string>

// Forward declaration of Publisher class
class Publisher;

class Subscriber {
public:
    virtual ~Subscriber() = default;

    // Method that will be called when a notification is received
    virtual void receive_notification(const std::vector<uint8_t>& message) = 0;
};
