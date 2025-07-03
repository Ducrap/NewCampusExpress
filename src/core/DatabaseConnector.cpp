#include "DatabaseConnector.h"
#include <stdexcept>
#include <iostream>

DatabaseConnector& DatabaseConnector::getInstance() {
    static DatabaseConnector instance;
    return instance;
}

DatabaseConnector::DatabaseConnector() : driver(nullptr), connected(false) {
    try {
        driver = sql::mysql::get_mysql_driver_instance();
    } catch (sql::SQLException& e) {
        std::cerr << "MySQL Driver error: " << e.what() << std::endl;
    }
}

DatabaseConnector::~DatabaseConnector() {
    if (connected) {
        connection->close();
    }
}

bool DatabaseConnector::connect(const std::string& host, const std::string& user, 
                              const std::string& password, const std::string& database) {
    try {
        connection.reset(driver->connect("tcp://" + host + ":3306", user, password));
        connection->setSchema(database);
        connected = true;
        return true;
    } catch (sql::SQLException& e) {
        std::cerr << "Connection error: " << e.what() << std::endl;
        connected = false;
        return false;
    }
}

std::unique_ptr<sql::ResultSet> DatabaseConnector::executeQuery(const std::string& query) {
    if (!connected) throw std::runtime_error("Database not connected");
    
    try {
        std::unique_ptr<sql::Statement> stmt(connection->createStatement());
        return std::unique_ptr<sql::ResultSet>(stmt->executeQuery(query));
    } catch (sql::SQLException& e) {
        std::cerr << "Query error: " << e.what() << std::endl;
        return nullptr;
    }
}

int DatabaseConnector::executeUpdate(const std::string& query) {
    if (!connected) throw std::runtime_error("Database not connected");
    
    try {
        std::unique_ptr<sql::Statement> stmt(connection->createStatement());
        return stmt->executeUpdate(query);
    } catch (sql::SQLException& e) {
        std::cerr << "Update error: " << e.what() << std::endl;
        return -1;
    }
}

std::unique_ptr<sql::PreparedStatement> DatabaseConnector::prepareStatement(const std::string& query) {
    if (!connected) throw std::runtime_error("Database not connected");
    
    try {
        return std::unique_ptr<sql::PreparedStatement>(connection->prepareStatement(query));
    } catch (sql::SQLException& e) {
        std::cerr << "Prepare statement error: " << e.what() << std::endl;
        return nullptr;
    }
}

void DatabaseConnector::beginTransaction() {
    if (connected) connection->setAutoCommit(false);
}

void DatabaseConnector::commitTransaction() {
    if (connected) {
        connection->commit();
        connection->setAutoCommit(true);
    }
}

void DatabaseConnector::rollbackTransaction() {
    if (connected) {
        connection->rollback();
        connection->setAutoCommit(true);
    }
}

bool DatabaseConnector::isConnected() const {
    return connected;
}