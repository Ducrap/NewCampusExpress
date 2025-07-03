// include/core/DatabaseConnector.h
#pragma once
#include <string>
#include <vector>

namespace CampusExpress {

struct UserInfo {
    std::string userId;
    std::string phone;
    std::string nickname;
    bool isStaff;
};

class IDatabaseConnector {
public:
    virtual ~IDatabaseConnector() = default;
    
    // 用户管理接口
    virtual bool registerUser(const std::string& phone, 
                            const std::string& password,
                            const std::string& nickname,
                            bool isStaff) = 0;
    
    virtual std::optional<UserInfo> authenticate(const std::string& identifier,
                                               const std::string& password) = 0;
    
    // 快递管理接口
    virtual bool addPackage(const std::string& trackingNumber,
                          const std::string& ownerPhone,
                          const std::string& shelfNumber,
                          bool isUrgent) = 0;
    
    virtual bool updatePackageStatus(const std::string& trackingNumber,
                                   const std::string& status) = 0;
    
    virtual std::vector<PackageInfo> getPackagesByUser(const std::string& phone) = 0;
    
    // 事务支持
    virtual bool beginTransaction() = 0;
    virtual bool commitTransaction() = 0;
    virtual bool rollbackTransaction() = 0;
};

// 创建具体实现的工厂方法
std::unique_ptr<IDatabaseConnector> createMySQLConnector(
    const std::string& host, 
    const std::string& user,
    const std::string& password,
    const std::string& database);

} // namespace CampusExpress