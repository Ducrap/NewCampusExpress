#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "User.h"
#include "DatabaseConnector.h"
#include <vector>
#include <optional>

class UserManager {
public:
    explicit UserManager(DatabaseConnector& dbConnector);
    
    // 添加用户
    bool addUser(const User& user);
    
    // 删除用户
    bool deleteUser(const std::string& userId);
    
    // 更新用户信息
    bool updateUser(const User& user);
    
    // 查询单个用户
    std::optional<User> findUserById(const std::string& userId);
    std::optional<User> findUserByPhone(const std::string& phone);
    
    // 验证用户登录
    std::optional<User> authenticateUser(const std::string& identifier, const std::string& password);
    
    // 获取所有用户
    std::vector<User> getAllUsers();
    
    // 筛选用户
    std::vector<User> filterUsers(UserType type);
    
    // 统计用户数量
    int countUsers() const;
    
    // 检查用户ID是否存在
    bool userIdExists(const std::string& userId) const;
    
    // 检查手机号是否存在
    bool userPhoneExists(const std::string& phone) const;

private:
    DatabaseConnector& dbConnector;
    
    // 从数据库加载用户
    std::optional<User> loadUserFromDB(const std::string& query, const std::string& param);
    
    // 保存用户到数据库
    bool saveUserToDB(const User& user, bool isNewUser);
};

#endif // USERMANAGER_H