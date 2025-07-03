#ifndef DATABASECONNECTOR_H
#define DATABASECONNECTOR_H

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <string>
#include <memory>

class DatabaseConnector {
public:
    // 获取数据库连接单例
    static DatabaseConnector& getInstance();
    
    // 连接数据库
    bool connect(const std::string& host, const std::string& user, 
                const std::string& password, const std::string& database);
    
    // 执行查询
    std::unique_ptr<sql::ResultSet> executeQuery(const std::string& query);
    
    // 执行更新
    int executeUpdate(const std::string& query);
    
    // 准备语句
    std::unique_ptr<sql::PreparedStatement> prepareStatement(const std::string& query);
    
    // 事务管理
    void beginTransaction();
    void commitTransaction();
    void rollbackTransaction();
    
    // 检查连接状态
    bool isConnected() const;

private:
    DatabaseConnector(); // 私有构造函数
    ~DatabaseConnector();
    
    sql::mysql::MySQL_Driver* driver;
    std::unique_ptr<sql::Connection> connection;
    bool connected;
};

#endif // DATABASECONNECTOR_H