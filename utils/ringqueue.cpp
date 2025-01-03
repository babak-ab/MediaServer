#include "RingQueue.hpp"

// Append bytes to the ring queue
bool IRingQueue::append(const uint8_t* data, size_t length)
{
    if (length > available_space()) {
        std::cerr << "Not enough space in the buffer to append data." << std::endl;
        return false; // Not enough space
    }

    for (size_t i = 0; i < length; ++i) {
        buffer_[tail_] = data[i];
        tail_ = (tail_ + 1) % buffer_.size();
    }
    size_ += length;
    return true;
}
bool IRingQueue::get_bytes(uint8_t* dest, size_t length)
{
    if (length > size_) {
        std::cerr << "Not enough data to read." << std::endl;
        return false; // Not enough data to read
    }

    for (size_t i = 0; i < length; ++i) {
        dest[i] = buffer_[head_];
        head_ = (head_ + 1) % buffer_.size();
    }
    size_ -= length;
    return true;
}
