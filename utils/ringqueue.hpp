
#pragma once
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <condition_variable>
class IRingQueue {
public:
    explicit IRingQueue()
    {
    }

    virtual ~IRingQueue() = default;
    bool append(const uint8_t* data, size_t length);
    void get_bytes(uint8_t* dest, size_t length);

    // Retrieve bytes from the ring queue

    // Pure virtual method to detect and extract a valid packet struct
    virtual void find_packet(const std::vector<uint8_t>& packet) = 0;

protected:
    std::queue<int> _queue;
    std::mutex _queueMutex; // Mutex to synchronize access to the queue
    std::condition_variable _condition;
    // Get available space in the buffer
    size_t size() const
    {
        return _queue.size();
    }
};