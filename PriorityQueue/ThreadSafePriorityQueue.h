#ifndef THREAD_SAFE_PRIORITY_QUEUE_H
#define THREAD_SAFE_PRIORITY_QUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>

template <typename T>
class ThreadSafePriorityQueue {
private:
    std::priority_queue<T> queue;
    std::mutex mut;
    std::condition_variable cv;
    bool abort_flag = false;

public:
    void push(T item) {
        std::lock_guard<std::mutex> lock(mut);
        queue.push(item);
        cv.notify_one();
    }

    std::shared_ptr<T> pop() {
        std::unique_lock<std::mutex> lock(mut);
        cv.wait(lock, [this] { return abort_flag || !queue.empty(); });
        if (abort_flag && queue.empty()) {
            return nullptr;
        }
        auto result = std::make_shared<T>(queue.top());
        queue.pop();
        return result;
    }

    void abort() {
        std::lock_guard<std::mutex> lock(mut);
        abort_flag = true;
        cv.notify_all();
    }

    size_t size() {
        std::lock_guard<std::mutex> lock(mut);
        return queue.size();
    }
};

#endif
