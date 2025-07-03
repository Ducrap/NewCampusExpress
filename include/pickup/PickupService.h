#ifndef PICKUPSERVICE_H
#define PICKUPSERVICE_H

#include "Package.h"
#include "DatabaseConnector.h"
#include <string>
#include <optional>

class PickupService {
public:
    explicit PickupService(DatabaseConnector& dbConnector);
    
    // 预约取件
    bool schedulePickup(const std::string& trackingNumber, const std::string& userPhone, bool isUrgent);
    
    // 查询快递位置
    std::optional<std::string> queryPackageLocation(const std::string& trackingNumber);
    
    // 完成取件
    bool completePickup(const std::string& trackingNumber);
    
    // 获取用户的所有快递
    std::vector<Package> getUserPackages(const std::string& userPhone);
    
    // 取消取件预约
    bool cancelPickup(const std::string& trackingNumber);

private:
    DatabaseConnector& dbConnector;
    
    // 从数据库加载快递信息
    std::optional<Package> loadPackageFromDB(const std::string& trackingNumber);
    
    // 更新数据库中的快递状态
    bool updatePackageInDB(const Package& package);
};

#endif // PICKUPSERVICE_H