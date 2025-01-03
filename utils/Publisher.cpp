#include "Publisher.hpp"
#include "Subscriber.hpp"
#include <algorithm>
#include <iostream>

void Publisher::add_subscriber(std::shared_ptr<Subscriber> subscriber) {
    subscribers_.push_back(subscriber);
}

void Publisher::remove_subscriber(std::shared_ptr<Subscriber> subscriber) {
    subscribers_.erase(std::remove(subscribers_.begin(), subscribers_.end(), subscriber), subscribers_.end());
}

void Publisher::notify_subscribers(const std::vector<uint8_t>& message) {
    for (auto& subscriber : subscribers_) {
        subscriber->receive_notification(message);
    }
}