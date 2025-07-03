#ifndef PICKUP_TYPES_H
#define PICKUP_TYPES_H

#include <string>

namespace Pickup {
    // 取件请求状态
    enum class RequestStatus {
        PENDING,    // 等待处理
        PROCESSING, // 处理中
        COMPLETED,  // 已完成
        CANCELLED   // 已取消
    };
    
    // 取件结果
    struct PickupResult {
        bool success;
        std::string message;
        std::string packageLocation;
    };
    
    // 快递查询结果
    struct PackageQueryResult {
        bool found;
        std::string trackingNumber;
        std::string shelfLocation;
        bool isUrgent;
        std::string status;
    };
}

#endif // PICKUP_TYPES_H