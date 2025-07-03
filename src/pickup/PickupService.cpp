#include "PickupService.h"
#include <sstream>

PickupService::PickupService(DatabaseConnector& dbConnector)
    : dbConnector(dbConnector) {}

bool PickupService::schedulePickup(const std::string& trackingNumber, 
                                 const std::string& userPhone, 
                                 bool isUrgent) {
    try {
        // 检查快递是否存在
        auto pkgOpt = loadPackageFromDB(trackingNumber);
        if (!pkgOpt) {
            return false;
        }
        
        Package& pkg = *pkgOpt;
        
        // 验证快递所有者
        if (pkg.getOwnerPhone() != userPhone) {
            return false;
        }
        
        // 更新急件状态
        if (isUrgent != pkg.isUrgent()) {
            pkg.setUrgent(isUrgent);
            if (!updatePackageInDB(pkg)) {
                return false;
            }
        }
        
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Schedule pickup error: " << e.what() << std::endl;
        return false;
    }
}

std::optional<std::string> PickupService::queryPackageLocation(const std::string& trackingNumber) {
    try {
        auto pkgOpt = loadPackageFromDB(trackingNumber);
        if (!pkgOpt) {
            return std::nullopt;
        }
        return pkgOpt->getShelfNumber();
    } catch (const std::exception& e) {
        std::cerr << "Query package error: " << e.what() << std::endl;
        return std::nullopt;
    }
}

bool PickupService::completePickup(const std::string& trackingNumber) {
    try {
        auto pkgOpt = loadPackageFromDB(trackingNumber);
        if (!pkgOpt) {
            return false;
        }
        
        Package& pkg = *pkgOpt;
        pkg.setPickupTime(std::time(nullptr));
        
        return updatePackageInDB(pkg);
    } catch (const std::exception& e) {
        std::cerr << "Complete pickup error: " << e.what() << std::endl;
        return false;
    }
}

std::vector<Package> PickupService::getUserPackages(const std::string& userPhone) {
    std::vector<Package> packages;
    
    try {
        auto stmt = dbConnector.prepareStatement(
            "SELECT tracking_number, owner_phone, shelf_number, is_urgent, "
            "arrival_time, pickup_time FROM packages WHERE owner_phone = ?");
        stmt->setString(1, userPhone);
        
        auto result = stmt->executeQuery();
        while (result->next()) {
            Package pkg(
                result->getString("tracking_number"),
                result->getString("owner_phone"),
                result->getString("shelf_number"),
                result->getBoolean("is_urgent"));
            
            pkg.setPickupTime(result->getInt64("pickup_time"));
            packages.push_back(pkg);
        }
    } catch (const std::exception& e) {
        std::cerr << "Get user packages error: " << e.what() << std::endl;
    }
    
    return packages;
}

bool PickupService::cancelPickup(const std::string& trackingNumber) {
    // 在这个简单实现中，取消取件只是从队列中移除
    // 实际项目中可能需要更复杂的逻辑
    return true;
}

std::optional<Package> PickupService::loadPackageFromDB(const std::string& trackingNumber) {
    try {
        auto stmt = dbConnector.prepareStatement(
            "SELECT tracking_number, owner_phone, shelf_number, is_urgent, "
            "arrival_time, pickup_time FROM packages WHERE tracking_number = ?");
        stmt->setString(1, trackingNumber);
        
        auto result = stmt->executeQuery();
        if (result->next()) {
            Package pkg(
                result->getString("tracking_number"),
                result->getString("owner_phone"),
                result->getString("shelf_number"),
                result->getBoolean("is_urgent"));
            
            pkg.setPickupTime(result->getInt64("pickup_time"));
            return pkg;
        }
    } catch (const std::exception& e) {
        std::cerr << "Load package error: " << e.what() << std::endl;
    }
    
    return std::nullopt;
}

bool PickupService::updatePackageInDB(const Package& package) {
    try {
        auto stmt = dbConnector.prepareStatement(
            "UPDATE packages SET shelf_number = ?, is_urgent = ?, "
            "pickup_time = ? WHERE tracking_number = ?");
        
        stmt->setString(1, package.getShelfNumber());
        stmt->setBoolean(2, package.isUrgent());
        stmt->setInt64(3, package.getPickupTime());
        stmt->setString(4, package.getTrackingNumber());
        
        return stmt->executeUpdate() > 0;
    } catch (const std::exception& e) {
        std::cerr << "Update package error: " << e.what() << std::endl;
        return false;
    }
}