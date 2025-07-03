#include "PickupQueue.h"
#include <algorithm>
#include <stdexcept>
void PickupQueue::enqueue(const Package& package) {
    std::lock_guard<std::mutex> lock(queueMutex);
    queue.push(package);
}

Package PickupQueue::dequeue() {
    std::lock_guard<std::mutex> lock(queueMutex);
    if (queue.empty()) {
        throw std::runtime_error("Cannot dequeue from empty queue");
    }
    
    Package pkg = queue.top();
    queue.pop();
    return pkg;
}

Package PickupQueue::peek() const {
    std::lock_guard<std::mutex> lock(queueMutex);
    if (queue.empty()) {
        throw std::runtime_error("Cannot peek empty queue");
    }
    return queue.top();
}

std::vector<Package> PickupQueue::getAllRequests() const {
    std::lock_guard<std::mutex> lock(queueMutex);
    std::vector<Package> packages;
    
    // 由于priority_queue没有迭代器，需要复制一份临时队列
    auto tempQueue = queue;
    while (!tempQueue.empty()) {
        packages.push_back(tempQueue.top());
        tempQueue.pop();
    }
    
    return packages;
}

size_t PickupQueue::size() const {
    std::lock_guard<std::mutex> lock(queueMutex);
    return queue.size();
}

bool PickupQueue::isEmpty() const {
    std::lock_guard<std::mutex> lock(queueMutex);
    return queue.empty();
}

void PickupQueue::clear() {
    std::lock_guard<std::mutex> lock(queueMutex);
    while (!queue.empty()) {
        queue.pop();
    }
}