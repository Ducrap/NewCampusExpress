#include "PackageManager.h"
#include <sstream>
#include <stdexcept>

PackageManager::PackageManager(DatabaseConnector& dbConnector)
    : dbConnector(dbConnector) {
    if (!syncFromDatabase()) {
        throw std::runtime_error("Failed to initialize package data from database");
    }
}

bool PackageManager::addPackage(const Package& package) {
    // 检查是否已存在
    if (packageTree.find(package.getTrackingNumber())) {
        return false;
    }

    // 添加到内存树
    packageTree.insert(package);

    // 持久化到数据库
    try {
        auto stmt = dbConnector.prepareStatement(
            "INSERT INTO packages (tracking_number, owner_phone, shelf_number, is_urgent, arrival_time) "
            "VALUES (?, ?, ?, ?, ?)");
        
        stmt->setString(1, package.getTrackingNumber());
        stmt->setString(2, package.getOwnerPhone());
        stmt->setString(3, package.getShelfNumber());
        stmt->setBoolean(4, package.isUrgent());
        stmt->setInt64(5, package.getArrivalTime());
        
        return stmt->executeUpdate() > 0;
    } catch (const sql::SQLException& e) {
        // 回滚内存操作
        packageTree.remove(package.getTrackingNumber());
        std::cerr << "SQL Error adding package: " << e.what() << std::endl;
        return false;
    }
}

bool PackageManager::deletePackage(const std::string& trackingNumber) {
    // 从内存树中移除
    if (!packageTree.remove(trackingNumber)) {
        return false;
    }

    // 从数据库删除
    try {
        auto stmt = dbConnector.prepareStatement(
            "DELETE FROM packages WHERE tracking_number = ?");
        stmt->setString(1, trackingNumber);
        
        return stmt->executeUpdate() > 0;
    } catch (const sql::SQLException& e) {
        // 重新加载数据保持一致性
        syncFromDatabase();
        std::cerr << "SQL Error deleting package: " << e.what() << std::endl;
        return false;
    }
}

bool PackageManager::updatePackage(const Package& package) {
    // 更新内存树
    if (!packageTree.update(package)) {
        return false;
    }

    // 更新数据库
    try {
        auto stmt = dbConnector.prepareStatement(
            "UPDATE packages SET owner_phone = ?, shelf_number = ?, is_urgent = ?, "
            "pickup_time = ? WHERE tracking_number = ?");
        
        stmt->setString(1, package.getOwnerPhone());
        stmt->setString(2, package.getShelfNumber());
        stmt->setBoolean(3, package.isUrgent());
        stmt->setInt64(4, package.getPickupTime());
        stmt->setString(5, package.getTrackingNumber());
        
        return stmt->executeUpdate() > 0;
    } catch (const sql::SQLException& e) {
        // 重新加载数据保持一致性
        syncFromDatabase();
        std::cerr << "SQL Error updating package: " << e.what() << std::endl;
        return false;
    }
}

std::optional<Package> PackageManager::findPackage(const std::string& trackingNumber) {
    if (auto pkg = packageTree.find(trackingNumber)) {
        return *pkg;
    }
    return std::nullopt;
}

std::vector<Package> PackageManager::getAllPackages() {
    return packageTree.getAll();
}

std::vector<Package> PackageManager::filterPackages(
    const std::string& ownerPhoneFilter,
    bool urgentOnly,
    bool notPickedUpOnly) {
    
    auto allPackages = packageTree.getAll();
    std::vector<Package> result;
    
    for (const auto& pkg : allPackages) {
        // 过滤条件
        bool match = true;
        
        if (!ownerPhoneFilter.empty() && pkg.getOwnerPhone().find(ownerPhoneFilter) == std::string::npos) {
            match = false;
        }
        
        if (urgentOnly && !pkg.isUrgent()) {
            match = false;
        }
        
        if (notPickedUpOnly && pkg.getPickupTime() != 0) {
            match = false;
        }
        
        if (match) {
            result.push_back(pkg);
        }
    }
    
    return result;
}

int PackageManager::countPackages() const {
    return packageTree.getAll().size();
}

bool PackageManager::syncFromDatabase() {
    return loadAllPackagesFromDB();
}

bool PackageManager::saveToDatabase() {
    try {
        dbConnector.beginTransaction();
        
        // 清空表
        dbConnector.executeUpdate("TRUNCATE TABLE packages");
        
        // 重新插入所有数据
        auto allPackages = packageTree.getAll();
        for (const auto& pkg : allPackages) {
            if (!savePackageToDB(pkg)) {
                dbConnector.rollbackTransaction();
                return false;
            }
        }
        
        dbConnector.commitTransaction();
        return true;
    } catch (const std::exception& e) {
        dbConnector.rollbackTransaction();
        std::cerr << "Error saving packages to DB: " << e.what() << std::endl;
        return false;
    }
}

bool PackageManager::loadAllPackagesFromDB() {
    try {
        packageTree.clear();
        
        auto result = dbConnector.executeQuery(
            "SELECT tracking_number, owner_phone, shelf_number, is_urgent, "
            "arrival_time, pickup_time FROM packages");
        
        while (result->next()) {
            Package pkg(
                result->getString("tracking_number"),
                result->getString("owner_phone"),
                result->getString("shelf_number"),
                result->getBoolean("is_urgent"));
            
            pkg.setPickupTime(result->getInt64("pickup_time"));
            packageTree.insert(pkg);
        }
        
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error loading packages from DB: " << e.what() << std::endl;
        return false;
    }
}

bool PackageManager::savePackageToDB(const Package& package) {
    try {
        auto stmt = dbConnector.prepareStatement(
            "INSERT INTO packages (tracking_number, owner_phone, shelf_number, "
            "is_urgent, arrival_time, pickup_time) VALUES (?, ?, ?, ?, ?, ?)");
        
        stmt->setString(1, package.getTrackingNumber());
        stmt->setString(2, package.getOwnerPhone());
        stmt->setString(3, package.getShelfNumber());
        stmt->setBoolean(4, package.isUrgent());
        stmt->setInt64(5, package.getArrivalTime());
        stmt->setInt64(6, package.getPickupTime());
        
        return stmt->executeUpdate() > 0;
    } catch (const std::exception& e) {
        std::cerr << "Error saving package to DB: " << e.what() << std::endl;
        return false;
    }
}