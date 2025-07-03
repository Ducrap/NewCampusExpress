#include "LoginWindow.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QRegularExpressionValidator>

LoginWindow::LoginWindow(DatabaseConnector& dbConnector, QWidget* parent)
    : QMainWindow(parent), dbConnector(dbConnector) {
    setupLoginUI();
    setupRegisterUI();
    
    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(loginPage);
    stackedWidget->addWidget(registerPage);
    setCentralWidget(stackedWidget);
    
    setWindowTitle("校园快递驿站管理系统 - 登录");
    resize(400, 300);
}

void LoginWindow::setupLoginUI() {
    loginPage = new QWidget(this);
    
    QVBoxLayout* layout = new QVBoxLayout(loginPage);
    
    // 用户类型选择
    userTypeCombo = new QComboBox(loginPage);
    userTypeCombo->addItem("学生用户", QVariant::fromValue(UserType::STUDENT));
    userTypeCombo->addItem("工作人员", QVariant::fromValue(UserType::STAFF));
    
    // 登录表单
    QFormLayout* formLayout = new QFormLayout();
    loginIdentifierEdit = new QLineEdit(loginPage);
    loginIdentifierEdit->setPlaceholderText("输入手机号或用户ID");
    
    loginPasswordEdit = new QLineEdit(loginPage);
    loginPasswordEdit->setPlaceholderText("输入密码");
    loginPasswordEdit->setEchoMode(QLineEdit::Password);
    
    formLayout->addRow("用户类型:", userTypeCombo);
    formLayout->addRow("账号:", loginIdentifierEdit);
    formLayout->addRow("密码:", loginPasswordEdit);
    
    // 按钮
    loginButton = new QPushButton("登录", loginPage);
    toRegisterButton = new QPushButton("注册新账号", loginPage);
    
    // 状态标签
    loginStatusLabel = new QLabel(loginPage);
    loginStatusLabel->setStyleSheet("color: red;");
    
    layout->addLayout(formLayout);
    layout->addWidget(loginButton);
    layout->addWidget(toRegisterButton);
    layout->addWidget(loginStatusLabel);
    
    // 连接信号槽
    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::handleLogin);
    connect(toRegisterButton, &QPushButton::clicked, this, &LoginWindow::switchToRegister);
}

void LoginWindow::setupRegisterUI() {
    registerPage = new QWidget(this);
    
    QVBoxLayout* layout = new QVBoxLayout(registerPage);
    
    // 注册表单
    QFormLayout* formLayout = new QFormLayout();
    
    // 手机号验证器
    QRegularExpression phoneRegex("^1[3-9]\\d{9}$");
    QValidator* phoneValidator = new QRegularExpressionValidator(phoneRegex, this);
    
    registerPhoneEdit = new QLineEdit(registerPage);
    registerPhoneEdit->setPlaceholderText("11位手机号");
    registerPhoneEdit->setValidator(phoneValidator);
    
    registerPasswordEdit = new QLineEdit(registerPage);
    registerPasswordEdit->setPlaceholderText("设置密码");
    registerPasswordEdit->setEchoMode(QLineEdit::Password);
    
    registerConfirmEdit = new QLineEdit(registerPage);
    registerConfirmEdit->setPlaceholderText("确认密码");
    registerConfirmEdit->setEchoMode(QLineEdit::Password);
    
    registerNicknameEdit = new QLineEdit(registerPage);
    registerNicknameEdit->setPlaceholderText("昵称");
    
    registerAsStaffCheck = new QCheckBox("注册为工作人员", registerPage);
    
    formLayout->addRow("手机号:", registerPhoneEdit);
    formLayout->addRow("密码:", registerPasswordEdit);
    formLayout->addRow("确认密码:", registerConfirmEdit);
    formLayout->addRow("昵称:", registerNicknameEdit);
    formLayout->addRow("", registerAsStaffCheck);
    
    // 按钮
    registerButton = new QPushButton("注册", registerPage);
    toLoginButton = new QPushButton("返回登录", registerPage);
    
    // 状态标签
    registerStatusLabel = new QLabel(registerPage);
    registerStatusLabel->setStyleSheet("color: red;");
    
    layout->addLayout(formLayout);
    layout->addWidget(registerButton);
    layout->addWidget(toLoginButton);
    layout->addWidget(registerStatusLabel);
    
    // 连接信号槽
    connect(registerButton, &QPushButton::clicked, this, &LoginWindow::handleRegister);
    connect(toLoginButton, &QPushButton::clicked, this, &LoginWindow::switchToLogin);
}

void LoginWindow::handleLogin() {
    QString identifier = loginIdentifierEdit->text().trimmed();
    QString password = loginPasswordEdit->text();
    UserType type = userTypeCombo->currentData().value<UserType>();
    
    if (identifier.isEmpty() || password.isEmpty()) {
        loginStatusLabel->setText("账号和密码不能为空");
        return;
    }
    
    // 在实际应用中，这里应该调用UserManager进行认证
    // 这里简化为直接发出登录成功信号
    emit userLoggedIn(identifier, type == UserType::STAFF);
}

void LoginWindow::handleRegister() {
    QString phone = registerPhoneEdit->text().trimmed();
    QString password = registerPasswordEdit->text();
    QString confirm = registerConfirmEdit->text();
    QString nickname = registerNicknameEdit->text().trimmed();
    bool isStaff = registerAsStaffCheck->isChecked();
    
    // 验证输入
    if (phone.isEmpty() || password.isEmpty() || confirm.isEmpty()) {
        registerStatusLabel->setText("手机号和密码不能为空");
        return;
    }
    
    if (password != confirm) {
        registerStatusLabel->setText("两次输入的密码不一致");
        return;
    }
    
    if (nickname.isEmpty()) {
        nickname = "用户" + phone.right(4);
    }
    
    // 在实际应用中，这里应该调用UserManager创建用户
    // 这里简化为直接发出注册成功信号并返回登录页
    registerStatusLabel->setText("注册成功！");
    QTimer::singleShot(1000, this, &LoginWindow::switchToLogin);
}

void LoginWindow::switchToRegister() {
    stackedWidget->setCurrentWidget(registerPage);
    setWindowTitle("校园快递驿站管理系统 - 注册");
    clearFields();
}

void LoginWindow::switchToLogin() {
    stackedWidget->setCurrentWidget(loginPage);
    setWindowTitle("校园快递驿站管理系统 - 登录");
    clearFields();
}

void LoginWindow::clearFields() {
    loginIdentifierEdit->clear();
    loginPasswordEdit->clear();
    loginStatusLabel->clear();
    
    registerPhoneEdit->clear();
    registerPasswordEdit->clear();
    registerConfirmEdit->clear();
    registerNicknameEdit->clear();
    registerAsStaffCheck->setChecked(false);
    registerStatusLabel->clear();
}