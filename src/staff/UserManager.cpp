#include "UserManager.h"
#include <stdexcept>
#include <iomanip>
#include <sstream>
#include <ctime>

UserManager::UserManager(DatabaseConnector& dbConnector)
    : dbConnector(dbConnector) {}

bool UserManager::addUser(const User& user) {
    try {
        auto stmt = dbConnector.prepareStatement(
            "INSERT INTO users (user_id, phone, password, nickname, user_type) "
            "VALUES (?, ?, ?, ?, ?)");
        
        stmt->setString(1, user.getId());
        stmt->setString(2, user.getPhone());
        stmt->setString(3, user.getPassword());
        stmt->setString(4, user.getNickname());
        stmt->setInt(5, static_cast<int>(user.getType()));
        
        return stmt->executeUpdate() > 0;
    } catch (const sql::SQLException& e) {
        std::cerr << "SQL Error adding user: " << e.what() << std::endl;
        return false;
    }
}

bool UserManager::deleteUser(const std::string& userId) {
    try {
        auto stmt = dbConnector.prepareStatement(
            "DELETE FROM users WHERE user_id = ?");
        stmt->setString(1, userId);
        
        return stmt->executeUpdate() > 0;
    } catch (const sql::SQLException& e) {
        std::cerr << "SQL Error deleting user: " << e.what() << std::endl;
        return false;
    }
}

bool UserManager::updateUser(const User& user) {
    try {
        auto stmt = dbConnector.prepareStatement(
            "UPDATE users SET phone = ?, password = ?, nickname = ?, user_type = ? "
            "WHERE user_id = ?");
        
        stmt->setString(1, user.getPhone());
        stmt->setString(2, user.getPassword());
        stmt->setString(3, user.getNickname());
        stmt->setInt(4, static_cast<int>(user.getType()));
        stmt->setString(5, user.getId());
        
        return stmt->executeUpdate() > 0;
    } catch (const sql::SQLException& e) {
        std::cerr << "SQL Error updating user: " << e.what() << std::endl;
        return false;
    }
}

std::optional<User> UserManager::findUserById(const std::string& userId) {
    return loadUserFromDB("SELECT * FROM users WHERE user_id = ?", userId);
}

std::optional<User> UserManager::findUserByPhone(const std::string& phone) {
    return loadUserFromDB("SELECT * FROM users WHERE phone = ?", phone);
}

std::optional<User> UserManager::authenticateUser(const std::string& identifier, const std::string& password) {
    try {
        // 尝试通过ID或手机号查找
        auto stmt = dbConnector.prepareStatement(
            "SELECT * FROM users WHERE user_id = ? OR phone = ?");
        stmt->setString(1, identifier);
        stmt->setString(2, identifier);
        
        auto result = stmt->executeQuery();
        if (result->next()) {
            User user(
                result->getString("user_id"),
                result->getString("phone"),
                result->getString("password"),
                result->getString("nickname"),
                static_cast<UserType>(result->getInt("user_type")));
            
            if (user.verifyPassword(password)) {
                return user;
            }
        }
    } catch (const sql::SQLException& e) {
        std::cerr << "SQL Error authenticating user: " << e.what() << std::endl;
    }
    
    return std::nullopt;
}

std::vector<User> UserManager::getAllUsers() {
    std::vector<User> users;
    
    try {
        auto result = dbConnector.executeQuery("SELECT * FROM users");
        while (result->next()) {
            users.emplace_back(
                result->getString("user_id"),
                result->getString("phone"),
                result->getString("password"),
                result->getString("nickname"),
                static_cast<UserType>(result->getInt("user_type")));
        }
    } catch (const sql::SQLException& e) {
        std::cerr << "SQL Error getting all users: " << e.what() << std::endl;
    }
    
    return users;
}

std::vector<User> UserManager::filterUsers(UserType type) {
    std::vector<User> filteredUsers;
    auto allUsers = getAllUsers();
    
    std::copy_if(allUsers.begin(), allUsers.end(), std::back_inserter(filteredUsers),
        [type](const User& user) { return user.getType() == type; });
    
    return filteredUsers;
}

int UserManager::countUsers() const {
    try {
        auto result = dbConnector.executeQuery("SELECT COUNT(*) AS count FROM users");
        if (result->next()) {
            return result->getInt("count");
        }
    } catch (const sql::SQLException& e) {
        std::cerr << "SQL Error counting users: " << e.what() << std::endl;
    }
    return 0;
}

bool UserManager::userIdExists(const std::string& userId) const {
    try {
        auto stmt = dbConnector.prepareStatement(
            "SELECT 1 FROM users WHERE user_id = ?");
        stmt->setString(1, userId);
        
        auto result = stmt->executeQuery();
        return result->next();
    } catch (const sql::SQLException& e) {
        std::cerr << "SQL Error checking user ID: " << e.what() << std::endl;
        return false;
    }
}

bool UserManager::userPhoneExists(const std::string& phone) const {
    try {
        auto stmt = dbConnector.prepareStatement(
            "SELECT 1 FROM users WHERE phone = ?");
        stmt->setString(1, phone);
        
        auto result = stmt->executeQuery();
        return result->next();
    } catch (const sql::SQLException& e) {
        std::cerr << "SQL Error checking phone: " << e.what() << std::endl;
        return false;
    }
}

std::optional<User> UserManager::loadUserFromDB(const std::string& query, const std::string& param) {
    try {
        auto stmt = dbConnector.prepareStatement(query);
        stmt->setString(1, param);
        
        auto result = stmt->executeQuery();
        if (result->next()) {
            return User(
                result->getString("user_id"),
                result->getString("phone"),
                result->getString("password"),
                result->getString("nickname"),
                static_cast<UserType>(result->getInt("user_type")));
        }
    } catch (const sql::SQLException& e) {
        std::cerr << "SQL Error loading user: " << e.what() << std::endl;
    }
    
    return std::nullopt;
}

bool UserManager::saveUserToDB(const User& user, bool isNewUser) {
    try {
        std::unique_ptr<sql::PreparedStatement> stmt;
        
        if (isNewUser) {
            stmt = dbConnector.prepareStatement(
                "INSERT INTO users (user_id, phone, password, nickname, user_type) "
                "VALUES (?, ?, ?, ?, ?)");
        } else {
            stmt = dbConnector.prepareStatement(
                "UPDATE users SET phone = ?, password = ?, nickname = ?, user_type = ? "
                "WHERE user_id = ?");
        }
        
        if (isNewUser) {
            stmt->setString(1, user.getId());
            stmt->setString(2, user.getPhone());
            stmt->setString(3, user.getPassword());
            stmt->setString(4, user.getNickname());
            stmt->setInt(5, static_cast<int>(user.getType()));
        } else {
            stmt->setString(1, user.getPhone());
            stmt->setString(2, user.getPassword());
            stmt->setString(3, user.getNickname());
            stmt->setInt(4, static_cast<int>(user.getType()));
            stmt->setString(5, user.getId());
        }
        
        return stmt->executeUpdate() > 0;
    } catch (const sql::SQLException& e) {
        std::cerr << "SQL Error saving user: " << e.what() << std::endl;
        return false;
    }
}