#ifndef PICKUPSCHEDULER_H
#define PICKUPSCHEDULER_H

#include "PickupQueue.h"
#include "DatabaseConnector.h"
#include <vector>
#include <thread>
#include <atomic>

class PickupScheduler {
public:
    PickupScheduler(DatabaseConnector& dbConnector, int maxConcurrentPickups = 3);
    ~PickupScheduler();
    
    // 启动调度器
    void start();
    
    // 停止调度器
    void stop();
    
    // 添加取件请求
    void addPickupRequest(const Package& package);
    
    // 获取当前活跃取件数
    int getActivePickups() const;
    
    // 获取等待中的取件请求数
    int getWaitingRequests() const;
    
    // 设置最大并发取件数
    void setMaxConcurrentPickups(int max);

private:
    void processingLoop(); // 处理循环
    
    DatabaseConnector& dbConnector;
    PickupQueue pickupQueue;
    std::vector<std::thread> workerThreads;
    std::atomic<bool> running;
    std::atomic<int> activePickups;
    int maxConcurrentPickups;
    std::mutex schedulerMutex;
};

#endif // PICKUPSCHEDULER_H