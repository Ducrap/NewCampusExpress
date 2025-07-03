#include "include/core/DatabaseConnector.h"
#include "include/gui/LoginWindow.h"
#include "include/gui/UserWindow.h"
#include "include/gui/StaffWindow.h"
#include "include/pickup/PickupService.h"
#include "include/staff/StaffService.h"
#include <QApplication>
#include <QMessageBox>
#include <QSettings>
#include <QStyleFactory>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    // 设置应用程序信息
    QApplication::setApplicationName("CampusExpress");
    QApplication::setApplicationVersion("1.0.0");
    QApplication::setOrganizationName("University");
    
    // 设置全局样式
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    
    // 加载数据库配置
    QSettings settings;
    QString dbHost = settings.value("database/host", "localhost").toString();
    QString dbName = settings.value("database/name", "campus_express").toString();
    QString dbUser = settings.value("database/user", "root").toString();
    QString dbPass = settings.value("database/pass", "").toString();
    
    try {
        // 初始化数据库连接
        DatabaseConnector& dbConnector = DatabaseConnector::getInstance();
        if (!dbConnector.connect(dbHost.toStdString(), 
                                dbUser.toStdString(), 
                                dbPass.toStdString(), 
                                dbName.toStdString())) {
            QMessageBox::critical(nullptr, "数据库错误", "无法连接到数据库");
            return 1;
        }
        
        // 初始化服务
        PickupService pickupService(dbConnector);
        StaffService staffService(dbConnector);
        
        // 显示登录窗口
        LoginWindow loginWindow(dbConnector);
        loginWindow.show();
        
        // 连接登录信号
        QObject::connect(&loginWindow, &LoginWindow::userLoggedIn, 
            [&](const QString& userId, bool isStaff) {
                loginWindow.hide();
                
                if (isStaff) {
                    // 工作人员界面
                    StaffWindow* staffWindow = new StaffWindow(staffService);
                    staffWindow->show();
                    
                    // 窗口关闭时退出应用
                    QObject::connect(staffWindow, &StaffWindow::destroyed, 
                        [&]() { QApplication::quit(); });
                } else {
                    // 学生用户界面
                    UserWindow* userWindow = new UserWindow(pickupService, userId);
                    userWindow->show();
                    
                    // 窗口关闭时退出应用
                    QObject::connect(userWindow, &UserWindow::destroyed, 
                        [&]() { QApplication::quit(); });
                }
            });
        
        // 连接注册信号
        QObject::connect(&loginWindow, &LoginWindow::registrationRequested, 
            [&]() {
                // 这里可以添加注册成功后的处理逻辑
                QMessageBox::information(&loginWindow, "注册成功", "账号注册成功，请登录");
            });
        
        return app.exec();
        
    } catch (const std::exception& e) {
        QMessageBox::critical(nullptr, "系统错误", 
                             QString("系统初始化失败: %1").arg(e.what()));
        return 1;
    }
}