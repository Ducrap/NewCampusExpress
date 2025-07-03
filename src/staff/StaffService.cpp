#include "StaffService.h"
#include <ctime>
#include <iomanip>
#include <sstream>

StaffService::StaffService(DatabaseConnector& dbConnector)
    : packageManager(dbConnector), userManager(dbConnector) {}

bool StaffService::registerPackage(const std::string& trackingNumber,
                                const std::string& ownerPhone,
                                const std::string& shelfNumber,
                                bool isUrgent) {
    // 验证所有者是否存在
    if (!userManager.findUserByPhone(ownerPhone)) {
        return false;
    }
    
    Package pkg(trackingNumber, ownerPhone, shelfNumber, isUrgent);
    return packageManager.addPackage(pkg);
}

bool StaffService::updatePackageInfo(const std::string& trackingNumber,
                                   const std::string& newShelfNumber,
                                   bool newUrgentStatus) {
    auto pkgOpt = packageManager.findPackage(trackingNumber);
    if (!pkgOpt) {
        return false;
    }
    
    Package& pkg = *pkgOpt;
    pkg.setShelfNumber(newShelfNumber);
    pkg.setUrgent(newUrgentStatus);
    
    return packageManager.updatePackage(pkg);
}

bool StaffService::removePackage(const std::string& trackingNumber) {
    return packageManager.deletePackage(trackingNumber);
}

std::vector<Package> StaffService::searchPackages(const std::string& searchTerm) {
    return packageManager.filterPackages(searchTerm, false, false);
}

bool StaffService::registerUser(UserType type,
                              const std::string& phone,
                              const std::string& password,
                              const std::string& nickname) {
    // 检查手机号是否已存在
    if (userManager.userPhoneExists(phone)) {
        return false;
    }
    
    std::string userId = generateUserId(type);
    User user(userId, phone, password, nickname, type);
    return userManager.addUser(user);
}

bool StaffService::updateUserInfo(const std::string& userId,
                                const std::string& newPassword,
                                const std::string& newNickname) {
    auto userOpt = userManager.findUserById(userId);
    if (!userOpt) {
        return false;
    }
    
    User& user = *userOpt;
    if (!newPassword.empty()) {
        user.setPassword(newPassword);
    }
    user.setNickname(newNickname);
    
    return userManager.updateUser(user);
}

bool StaffService::deleteUserAccount(const std::string& userId) {
    return userManager.deleteUser(userId);
}

std::vector<User> StaffService::listUsers(UserType type) {
    return userManager.filterUsers(type);
}

StaffService::Statistics StaffService::getSystemStatistics() {
    Statistics stats{};
    
    auto allPackages = packageManager.getAllPackages();
    stats.totalPackages = allPackages.size();
    
    stats.urgentPackages = std::count_if(allPackages.begin(), allPackages.end(),
        [](const Package& pkg) { return pkg.isUrgent(); });
    
    // 获取今天取件的快递数
    time_t now = std::time(nullptr);
    struct tm* today = std::localtime(&now);
    today->tm_hour = 0;
    today->tm_min = 0;
    today->tm_sec = 0;
    time_t todayStart = std::mktime(today);
    
    stats.pickedUpToday = std::count_if(allPackages.begin(), allPackages.end(),
        [todayStart](const Package& pkg) { 
            return pkg.getPickupTime() >= todayStart; 
        });
    
    auto allUsers = userManager.getAllUsers();
    stats.registeredUsers = allUsers.size();
    
    stats.staffCount = std::count_if(allUsers.begin(), allUsers.end(),
        [](const User& user) { return user.isStaff(); });
    
    return stats;
}

std::string StaffService::generateUserId(UserType type) const {
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    
    std::ostringstream oss;
    oss << (type == UserType::STAFF ? "S" : "U")
        << std::put_time(localTime, "%Y%m%d%H%M%S")
        << std::rand() % 1000; // 添加随机部分避免冲突
    
    return oss.str();
}

bool StaffService::validatePackageInfo(const std::string& trackingNumber,
                                     const std::string& ownerPhone) const {
    // 检查快递单号格式 (简单示例)
    if (trackingNumber.empty() || trackingNumber.length() < 8) {
        return false;
    }
    
    // 检查手机号格式 (简单示例)
    if (ownerPhone.empty() || ownerPhone.length() != 11) {
        return false;
    }
    
    return true;
}