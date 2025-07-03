#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "DatabaseConnector.h"

QT_BEGIN_NAMESPACE
class QLineEdit;
class QPushButton;
class QComboBox;
class QLabel;
class QCheckBox;
QT_END_NAMESPACE

class LoginWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit LoginWindow(DatabaseConnector& dbConnector, QWidget* parent = nullptr);
    ~LoginWindow();

signals:
    void userLoggedIn(const QString& userId, bool isStaff);
    void registrationRequested();

private slots:
    void handleLogin();
    void handleRegister();
    void switchToRegister();
    void switchToLogin();

private:
    void setupLoginUI();
    void setupRegisterUI();
    void clearFields();

    DatabaseConnector& dbConnector;
    QStackedWidget* stackedWidget;
    
    // Login Page
    QWidget* loginPage;
    QComboBox* userTypeCombo;
    QLineEdit* loginIdentifierEdit;
    QLineEdit* loginPasswordEdit;
    QPushButton* loginButton;
    QPushButton* toRegisterButton;
    QLabel* loginStatusLabel;
    
    // Register Page
    QWidget* registerPage;
    QLineEdit* registerPhoneEdit;
    QLineEdit* registerPasswordEdit;
    QLineEdit* registerConfirmEdit;
    QLineEdit* registerNicknameEdit;
    QCheckBox* registerAsStaffCheck;
    QPushButton* registerButton;
    QPushButton* toLoginButton;
    QLabel* registerStatusLabel;
};

#endif // LOGINWINDOW_H