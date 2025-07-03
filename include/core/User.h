#ifndef USER_H
#define USER_H

#include <string>
#include <stdexcept>

enum class UserType {
    STUDENT,
    STAFF
};

class User {
public:
    User(const std::string& id, const std::string& phone, 
         const std::string& password, const std::string& nickname, 
         UserType type);
    
    // Getters
    std::string getId() const;
    std::string getPhone() const;
    std::string getPassword() const;
    std::string getNickname() const;
    UserType getType() const;
    
    // Setters
    void setPassword(const std::string& newPassword);
    void setNickname(const std::string& newNickname);
    
    // 验证密码
    bool verifyPassword(const std::string& inputPassword) const;
    
    // 用户类型检查
    bool isStudent() const;
    bool isStaff() const;

private:
    std::string id;
    std::string phone;
    std::string password; // 实际应用中应该存储哈希值
    std::string nickname;
    UserType type;
};

#endif // USER_H