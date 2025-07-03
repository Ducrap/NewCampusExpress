#include "PickupScheduler.h"
#include <thread>
#include <chrono>

PickupScheduler::PickupScheduler(DatabaseConnector& dbConnector, int maxConcurrentPickups)
    : dbConnector(dbConnector),
      running(false),
      activePickups(0),
      maxConcurrentPickups(maxConcurrentPickups) {}

PickupScheduler::~PickupScheduler() {
    stop();
}

void PickupScheduler::start() {
    if (running) return;
    
    running = true;
    workerThreads.emplace_back(&PickupScheduler::processingLoop, this);
}

void PickupScheduler::stop() {
    running = false;
    for (auto& thread : workerThreads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
    workerThreads.clear();
}

void PickupScheduler::addPickupRequest(const Package& package) {
    pickupQueue.enqueue(package);
}

int PickupScheduler::getActivePickups() const {
    return activePickups.load();
}

int PickupScheduler::getWaitingRequests() const {
    return pickupQueue.size();
}

void PickupScheduler::setMaxConcurrentPickups(int max) {
    std::lock_guard<std::mutex> lock(schedulerMutex);
    maxConcurrentPickups = max;
}

void PickupScheduler::processingLoop() {
    while (running) {
        // 检查是否有可用槽位
        if (activePickups.load() >= maxConcurrentPickups) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            continue;
        }
        
        // 尝试获取下一个请求
        if (pickupQueue.isEmpty()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            continue;
        }
        
        // 处理取件请求
        try {
            Package pkg = pickupQueue.dequeue();
            activePickups++;
            
            // 模拟取件处理过程
            std::thread([this, pkg]() {
                // 更新数据库中的取件状态
                try {
                    auto stmt = dbConnector.prepareStatement(
                        "UPDATE packages SET pickup_time = ? WHERE tracking_number = ?");
                    stmt->setInt64(1, std::time(nullptr));
                    stmt->setString(2, pkg.getTrackingNumber());
                    stmt->executeUpdate();
                    
                    // 模拟取件耗时
                    std::this_thread::sleep_for(std::chrono::seconds(3));
                } catch (const std::exception& e) {
                    std::cerr << "Pickup processing error: " << e.what() << std::endl;
                }
                
                activePickups--;
            }).detach();
            
        } catch (const std::exception& e) {
            std::cerr << "Error processing pickup: " << e.what() << std::endl;
        }
    }
}