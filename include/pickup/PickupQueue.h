#ifndef PICKUPQUEUE_H
#define PICKUPQUEUE_H

#include "Package.h"
#include <queue>
#include <vector>
#include <mutex>

class PickupQueue {
public:
    // 添加取件请求
    void enqueue(const Package& package);
    
    // 处理下一个取件请求
    Package dequeue();
    
    // 查看但不移除下一个取件请求
    Package peek() const;
    
    // 获取队列中所有请求
    std::vector<Package> getAllRequests() const;
    
    // 获取队列大小
    size_t size() const;
    
    // 检查队列是否为空
    bool isEmpty() const;
    
    // 清空队列
    void clear();

private:
    // 自定义比较器，急件优先
    struct ComparePriority {
        bool operator()(const Package& lhs, const Package& rhs) const {
            // 急件优先，如果都是急件或都不是，按到达时间排序
            if (lhs.isUrgent() && !rhs.isUrgent()) return false;
            if (!lhs.isUrgent() && rhs.isUrgent()) return true;
            return lhs.getArrivalTime() > rhs.getArrivalTime();
        }
    };
    
    std::priority_queue<Package, std::vector<Package>, ComparePriority> queue;
    mutable std::mutex queueMutex; // 线程安全
};

#endif // PICKUPQUEUE_H