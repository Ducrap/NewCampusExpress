#ifndef STAFFSERVICE_H
#define STAFFSERVICE_H

#include "PackageManager.h"
#include "UserManager.h"
#include <string>
#include <vector>

class StaffService {
public:
    StaffService(DatabaseConnector& dbConnector);
    
    // 快递管理
    bool registerPackage(const std::string& trackingNumber,
                        const std::string& ownerPhone,
                        const std::string& shelfNumber,
                        bool isUrgent);
    
    bool updatePackageInfo(const std::string& trackingNumber,
                          const std::string& newShelfNumber,
                          bool newUrgentStatus);
    
    bool removePackage(const std::string& trackingNumber);
    
    std::vector<Package> searchPackages(const std::string& searchTerm);
    
    // 用户管理
    bool registerUser(UserType type,
                     const std::string& phone,
                     const std::string& password,
                     const std::string& nickname);
    
    bool updateUserInfo(const std::string& userId,
                       const std::string& newPassword,
                       const std::string& newNickname);
    
    bool deleteUserAccount(const std::string& userId);
    
    std::vector<User> listUsers(UserType type);
    
    // 统计报表
    struct Statistics {
        int totalPackages;
        int urgentPackages;
        int pickedUpToday;
        int registeredUsers;
        int staffCount;
    };
    
    Statistics getSystemStatistics();

private:
    PackageManager packageManager;
    UserManager userManager;
    
    // 生成用户ID
    std::string generateUserId(UserType type) const;
    
    // 验证快递信息
    bool validatePackageInfo(const std::string& trackingNumber,
                           const std::string& ownerPhone) const;
};

#endif // STAFFSERVICE_H