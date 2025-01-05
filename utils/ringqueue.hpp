
#pragma once
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
template <typename T>
class IRingQueue {
public:
    explicit IRingQueue() = default;

    virtual ~IRingQueue() = default;

    bool append(const T& item)
    {

        std::unique_lock<std::mutex> lock(_queueMutex);

        _queue.push(item);
        _condition.notify_all();
        return true;
    }
    void get_items(std::vector<T>& buffer, size_t length)
    {
        std::unique_lock<std::mutex> lock(_queueMutex);

        _condition.wait(lock, [this, length] { return _queue.size() >= length; });

        // Copy the required number of bytes from the queue
        for (size_t i = 0; i < length; ++i) {
            buffer.push_back(_queue.front());
            _queue.pop(); // Remove the item from the queue
        }
    }

    // Retrieve bytes from the ring queue

protected:
    std::queue<T> _queue;
    std::mutex _queueMutex; // Mutex to synchronize access to the queue
    std::condition_variable _condition;
    // Get available space in the buffer
    size_t size() const
    {
        return _queue.size();
    }
};
