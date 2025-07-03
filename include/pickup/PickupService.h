// include/pickup/PickupService.h
#pragma once
#include "../core/Package.h"
#include <functional>

namespace CampusExpress {
namespace Pickup {

class IPickupService {
public:
    virtual ~IPickupService() = default;
    
    // 请求取件
    virtual bool requestPickup(const std::string& trackingNumber,
                             const std::string& userId,
                             bool isUrgent,
                             std::function<void(bool)> callback) = 0;
    
    // 查询队列状态
    struct QueueStatus {
        size_t waitingCount;
        size_t processingCount;
        size_t estimatedWaitTime; // 秒
    };
    
    virtual QueueStatus getQueueStatus() const = 0;
    
    // 事件通知
    using StatusUpdateCallback = std::function<void(QueueStatus)>;
    virtual void setStatusUpdateCallback(StatusUpdateCallback callback) = 0;
};

// 创建具体实现
std::unique_ptr<IPickupService> createPickupService(
    IDatabaseConnector& dbConnector,
    IAVLTreeManager& packageManager);

} // namespace Pickup
} // namespace CampusExpress