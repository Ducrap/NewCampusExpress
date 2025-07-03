#include "User.h"
#include <stdexcept>

User::User(const std::string& id, const std::string& phone, 
           const std::string& password, const std::string& nickname, 
           UserType type)
    : id(id), phone(phone), password(password), nickname(nickname), type(type) {
    if (id.empty() || phone.empty() || password.empty()) {
        throw std::invalid_argument("User fields cannot be empty");
    }
}

std::string User::getId() const { return id; }
std::string User::getPhone() const { return phone; }
std::string User::getPassword() const { return password; }
std::string User::getNickname() const { return nickname; }
UserType User::getType() const { return type; }

void User::setPassword(const std::string& newPassword) {
    if (newPassword.empty()) {
        throw std::invalid_argument("Password cannot be empty");
    }
    password = newPassword;
}

void User::setNickname(const std::string& newNickname) {
    nickname = newNickname;
}

bool User::verifyPassword(const std::string& inputPassword) const {
    return password == inputPassword;
}

bool User::isStudent() const { return type == UserType::STUDENT; }
bool User::isStaff() const { return type == UserType::STAFF; }