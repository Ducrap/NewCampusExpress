#ifndef PACKAGE_H
#define PACKAGE_H

#include <string>
#include <ctime>

class Package {
public:
    Package(const std::string& trackingNumber, 
            const std::string& ownerPhone,
            const std::string& shelfNumber,
            bool isUrgent = false);
    
    // Getters
    std::string getTrackingNumber() const;
    std::string getOwnerPhone() const;
    std::string getShelfNumber() const;
    bool isUrgent() const;
    time_t getArrivalTime() const;
    time_t getPickupTime() const;
    
    // Setters
    void setShelfNumber(const std::string& newShelfNumber);
    void setUrgent(bool urgent);
    void setPickupTime(time_t time);
    
    // 比较操作符
    bool operator<(const Package& other) const;
    bool operator==(const Package& other) const;

private:
    std::string trackingNumber;  // 快递单号 (唯一键)
    std::string ownerPhone;      // 收件人电话
    std::string shelfNumber;     // 货架号
    bool urgent;                 // 是否急件
    time_t arrivalTime;          // 到达时间
    time_t pickupTime;           // 取件时间 (0表示未取件)
};

#endif // PACKAGE_H