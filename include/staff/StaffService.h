// include/staff/StaffService.h
#pragma once
#include "../core/User.h"
#include "../core/Package.h"
#include <string>
#include <memory>
#include <optional>
#include <vector>

// Forward declaration for dependencies
namespace CampusExpress {
struct PackageInfo;
struct UserInfo;
class IDatabaseConnector;
class IAVLTreeManager;
}

namespace CampusExpress {
namespace Staff {

class IStaffService {
public:
    virtual ~IStaffService() = default;
    
    // 快递管理接口
    virtual bool addPackage(const PackageInfo& package) = 0;
    virtual bool removePackage(const std::string& trackingNumber) = 0;
    virtual std::optional<PackageInfo> findPackage(const std::string& trackingNumber) = 0;
    
    // 用户管理接口
    virtual std::vector<UserInfo> listUsers(int offset, int limit) = 0;
    virtual bool disableUser(const std::string& userId) = 0;
    
    // 系统状态
    struct SystemStatus {
        size_t totalPackages;
        size_t activeUsers;
        size_t todayPickups;
    };
    
    virtual SystemStatus getSystemStatus() const = 0;
};

// 创建具体实现
std::unique_ptr<IStaffService> createStaffService(
    IDatabaseConnector& dbConnector,
    IAVLTreeManager& packageManager);

} // namespace Staff
} // namespace CampusExpress