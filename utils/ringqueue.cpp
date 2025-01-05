#include "RingQueue.hpp"

// Append bytes to the ring queue
bool IRingQueue::append(const uint8_t* data, size_t length)
{
    std::unique_lock<std::mutex> lock(_queueMutex);

    for (size_t i = 0; i < length; ++i) {
        _queue.push(data[i]); // Append each byte to the queue
    }
    _condition.notify_all();
    return true;
}
void IRingQueue::get_bytes(uint8_t* dest, size_t length)
{
    std::unique_lock<std::mutex> lock(_queueMutex);

    _condition.wait(lock, [this, length] { return _queue.size() >= length; });

    // Copy the required number of bytes from the queue
    for (size_t i = 0; i < length; ++i) {
        dest[i] = _queue.front();
        _queue.pop();
    }
}
