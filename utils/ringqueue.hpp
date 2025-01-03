
#include <algorithm>
#include <iostream>
#include <vector>

class IRingQueue {
public:
    explicit IRingQueue(size_t capacity)
        : buffer_(capacity)
        , head_(0)
        , tail_(0)
        , size_(0)
    {
    }

    virtual ~IRingQueue() = default;
    bool append(const uint8_t* data, size_t length);
    bool get_bytes(uint8_t* dest, size_t length);

    // Retrieve bytes from the ring queue

    // Pure virtual method to detect and extract a valid packet struct
    virtual bool find_packet() = 0;

protected:
    std::vector<uint8_t> buffer_;
    size_t head_, tail_, size_;

    // Get available space in the buffer
    size_t available_space() const
    {
        return buffer_.size() - size_;
    }
};