#ifndef PACKAGEMANAGER_H
#define PACKAGEMANAGER_H

#include "Package.h"
#include "DatabaseConnector.h"
#include "AVLTree.h"
#include <vector>
#include <optional>

class PackageManager {
public:
    explicit PackageManager(DatabaseConnector& dbConnector);
    
    // 添加快递
    bool addPackage(const Package& package);
    
    // 删除快递
    bool deletePackage(const std::string& trackingNumber);
    
    // 更新快递信息
    bool updatePackage(const Package& package);
    
    // 查询单个快递
    std::optional<Package> findPackage(const std::string& trackingNumber);
    
    // 获取所有快递
    std::vector<Package> getAllPackages();
    
    // 根据条件筛选快递
    std::vector<Package> filterPackages(
        const std::string& ownerPhoneFilter = "",
        bool urgentOnly = false,
        bool notPickedUpOnly = false);
    
    // 统计快递数量
    int countPackages() const;
    
    // 从数据库同步数据
    bool syncFromDatabase();
    
    // 保存数据到数据库
    bool saveToDatabase();

private:
    DatabaseConnector& dbConnector;
    AVLTree<Package> packageTree; // 使用AVL树存储快递数据
    
    // 从数据库加载所有快递
    bool loadAllPackagesFromDB();
    
    // 保存单个快递到数据库
    bool savePackageToDB(const Package& package);
};

#endif // PACKAGEMANAGER_H