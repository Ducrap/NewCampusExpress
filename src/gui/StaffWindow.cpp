#include "StaffWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <ctime>
#include <iomanip>
#include <sstream>

StaffWindow::StaffWindow(StaffService& staffService, QWidget* parent)
    : QMainWindow(parent), staffService(staffService) {
    setupUI();
    
    setWindowTitle("校园快递驿站 - 工作人员界面");
    resize(1000, 700);
}

void StaffWindow::setupUI() {
    tabWidget = new QTabWidget(this);
    
    setupPackageTab();
    setupUserTab();
    setupStatsTab();
    
    statusLabel = new QLabel(this);
    statusLabel->setStyleSheet("color: green;");
    
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(statusLabel);
    
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

void StaffWindow::setupPackageTab() {
    packageTab = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(packageTab);
    
    // 表单区域
    QGroupBox* formGroup = new QGroupBox("快递管理", packageTab);
    QFormLayout* formLayout = new QFormLayout(formGroup);
    
    pkgTrackingEdit = new QLineEdit(packageTab);
    pkgTrackingEdit->setPlaceholderText("快递单号");
    
    pkgPhoneEdit = new QLineEdit(packageTab);
    pkgPhoneEdit->setPlaceholderText("收件人手机号");
    
    pkgShelfEdit = new QLineEdit(packageTab);
    pkgShelfEdit->setPlaceholderText("货架号");
    
    pkgUrgentCheck = new QCheckBox("急件", packageTab);
    
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    pkgAddButton = new QPushButton("添加快递", packageTab);
    pkgUpdateButton = new QPushButton("更新信息", packageTab);
    pkgDeleteButton = new QPushButton("删除快递", packageTab);
    pkgRefreshButton = new QPushButton("刷新列表", packageTab);
    
    buttonLayout->addWidget(pkgAddButton);
    buttonLayout->addWidget(pkgUpdateButton);
    buttonLayout->addWidget(pkgDeleteButton);
    buttonLayout->addWidget(pkgRefreshButton);
    
    formLayout->addRow("快递单号:", pkgTrackingEdit);
    formLayout->addRow("收件人手机:", pkgPhoneEdit);
    formLayout->addRow("货架位置:", pkgShelfEdit);
    formLayout->addRow("", pkgUrgentCheck);
    formLayout->addRow(buttonLayout);
    
    // 表格区域
    pkgTable = new QTableWidget(packageTab);
    pkgTable->setColumnCount(6);
    pkgTable->setHorizontalHeaderLabels({"快递单号", "收件人", "货架位置", "是否急件", "状态", "到达时间"});
    pkgTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    pkgTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    pkgTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    layout->addWidget(formGroup);
    layout->addWidget(pkgTable);
    
    tabWidget->addTab(packageTab, "快递管理");
    
    // 连接信号槽
    connect(pkgAddButton, &QPushButton::clicked, this, &StaffWindow::handlePackageRegistration);
    connect(pkgUpdateButton, &QPushButton::clicked, this, &StaffWindow::handlePackageUpdate);
    connect(pkgDeleteButton, &QPushButton::clicked, this, &StaffWindow::handlePackageDelete);
    connect(pkgRefreshButton, &QPushButton::clicked, this, &StaffWindow::refreshAllTabs);
    connect(pkgTable, &QTableWidget::cellClicked, this, &StaffWindow::showPackageDetails);
    
    loadAllPackages();
}

void StaffWindow::setupUserTab() {
    userTab = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(userTab);
    
    // 表单区域
    QGroupBox* formGroup = new QGroupBox("用户管理", userTab);
    QFormLayout* formLayout = new QFormLayout(formGroup);
    
    userTypeCombo = new QComboBox(userTab);
    userTypeCombo->addItem("学生用户", QVariant::fromValue(UserType::STUDENT));
    userTypeCombo->addItem("工作人员", QVariant::fromValue(UserType::STAFF));
    
    userPhoneEdit = new QLineEdit(userTab);
    userPhoneEdit->setPlaceholderText("手机号");
    
    userPasswordEdit = new QLineEdit(userTab);
    userPasswordEdit->setPlaceholderText("密码");
    userPasswordEdit->setEchoMode(QLineEdit::Password);
    
    userNicknameEdit = new QLineEdit(userTab);
    userNicknameEdit->setPlaceholderText("昵称");
    
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    userAddButton = new QPushButton("添加用户", userTab);
    userUpdateButton = new QPushButton("更新用户", userTab);
    userDeleteButton = new QPushButton("删除用户", userTab);
    userRefreshButton = new QPushButton("刷新列表", userTab);
    
    buttonLayout->addWidget(userAddButton);
    buttonLayout->addWidget(userUpdateButton);
    buttonLayout->addWidget(userDeleteButton);
    buttonLayout->addWidget(userRefreshButton);
    
    formLayout->addRow("用户类型:", userTypeCombo);
    formLayout->addRow("手机号:", userPhoneEdit);
    formLayout->addRow("密码:", userPasswordEdit);
    formLayout->addRow("昵称:", userNicknameEdit);
    formLayout->addRow(buttonLayout);
    
    // 表格区域
    userTable = new QTableWidget(userTab);
    userTable->setColumnCount(4);
    userTable->setHorizontalHeaderLabels({"用户ID", "手机号", "昵称", "用户类型"});
    userTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    userTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    userTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    layout->addWidget(formGroup);
    layout->addWidget(userTable);
    
    tabWidget->addTab(userTab, "用户管理");
    
    // 连接信号槽
    connect(userAddButton, &QPushButton::clicked, this, &StaffWindow::handleUserRegistration);
    connect(userUpdateButton, &QPushButton::clicked, this, &StaffWindow::handleUserUpdate);
    connect(userDeleteButton, &QPushButton::clicked, this, &StaffWindow::handleUserDelete);
    connect(userRefreshButton, &QPushButton::clicked, this, &StaffWindow::refreshAllTabs);
    connect(userTable, &QTableWidget::cellClicked, this, &StaffWindow::showUserDetails);
    
    loadAllUsers();
}

void StaffWindow::setupStatsTab() {
    statsTab = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(statsTab);
    
    QGroupBox* statsGroup = new QGroupBox("系统统计", statsTab);
    QFormLayout* statsLayout = new QFormLayout(statsGroup);
    
    totalPackagesLabel = new QLabel(statsTab);
    urgentPackagesLabel = new QLabel(statsTab);
    pickedUpTodayLabel = new QLabel(statsTab);
    totalUsersLabel = new QLabel(statsTab);
    staffCountLabel = new QLabel(statsTab);
    
    QPushButton* refreshButton = new QPushButton("刷新统计", statsTab);
    
    statsLayout->addRow("快递总数:", totalPackagesLabel);
    statsLayout->addRow("急件数量:", urgentPackagesLabel);
    statsLayout->addRow("今日取件:", pickedUpTodayLabel);
    statsLayout->addRow("用户总数:", totalUsersLabel);
    statsLayout->addRow("工作人员数:", staffCountLabel);
    statsLayout->addRow(refreshButton);
    
    layout->addWidget(statsGroup);
    tabWidget->addTab(statsTab, "系统统计");
    
    connect(refreshButton, &QPushButton::clicked, this, &StaffWindow::updateStats);
    
    updateStats();
}

// 其他成员函数实现...