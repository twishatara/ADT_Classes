#include <iostream>
#include "ThreadSafePriorityQueue.h"

class TextMessage {
public:
    std::string text;
    int priority;

    TextMessage(std::string t, int p) : text(t), priority(p) {}
    bool operator<(const TextMessage& other) const {
        return priority < other.priority;  // Higher priority comes first
    }
};

int main() {
    ThreadSafePriorityQueue<TextMessage> pq;

    pq.push(TextMessage("Low Priority", 1));
    pq.push(TextMessage("High Priority", 10));
    pq.push(TextMessage("Medium Priority", 5));

    std::cout << "Popped Message: " << pq.pop()->text << std::endl; // High Priority
    std::cout << "Popped Message: " << pq.pop()->text << std::endl; // Medium Priority
    std::cout << "Popped Message: " << pq.pop()->text << std::endl; // Low Priority

    return 0;
}
