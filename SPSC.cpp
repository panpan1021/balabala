#include <atomic>
#include <vector>
#include <optional>

template<typename T>
class SPSCQueue {
public:
    explicit SPSCQueue(size_t capacity)
        : buffer_(capacity + 1)  // 多一个空位用于区分满和空
        , head_(0), tail_(0)
    {
        // capacity 必须是 2 的幂？不需要，但模运算可优化为按位与（需为 2 的幂）
    }

    // 生产者调用
    bool push(const T& value) {
        size_t cur_tail = tail_.load(std::memory_order_relaxed);
        size_t next_tail = advance(cur_tail);
        if (next_tail == head_.load(std::memory_order_acquire)) {
            return false;   // 队列满
        }
        buffer_[cur_tail] = value;
        tail_.store(next_tail, std::memory_order_release);
        return true;
    }

    // 消费者调用
    std::optional<T> pop() {
        size_t cur_head = head_.load(std::memory_order_relaxed);
        if (cur_head == tail_.load(std::memory_order_acquire)) {
            return std::nullopt; // 队列空
        }
        T value = buffer_[cur_head];
        head_.store(advance(cur_head), std::memory_order_release);
        return value;
    }

private:
    size_t advance(size_t idx) const {
        return (idx + 1) % buffer_.size();
    }

    std::vector<T> buffer_;
    alignas(64) std::atomic<size_t> head_;   // 消费者索引
    alignas(64) std::atomic<size_t> tail_;   // 生产者索引
};