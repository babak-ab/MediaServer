// Publisher.hpp
#pragma once

#include <vector>
#include <memory>
#include <string>

// Forward declaration of Subscriber class
class Subscriber;

class Publisher {
public:
    // Method to add a subscriber
    void add_subscriber(std::shared_ptr<Subscriber> subscriber);

    // Method to remove a subscriber
    void remove_subscriber(std::shared_ptr<Subscriber> subscriber);

    // Method to notify all subscribers
    void notify_subscribers(const std::vector<uint8_t>& message);

private:
    std::vector<std::shared_ptr<Subscriber>> subscribers_;  // List of subscribers
};
