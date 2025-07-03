#include "UserWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QHeaderView>
#include <QMessageBox>

UserWindow::UserWindow(PickupService& pickupService, const QString& userId, QWidget* parent)
    : QMainWindow(parent), pickupService(pickupService), userId(userId) {
    setupUI();
    loadUserPackages();
    
    setWindowTitle("校园快递驿站 - 用户界面");
    resize(800, 600);
}

void UserWindow::setupUI() {
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    
    // 欢迎标签
    welcomeLabel = new QLabel(QString("欢迎您，用户 %1").arg(userId), this);
    welcomeLabel->setStyleSheet("font-size: 16px; font-weight: bold;");
    mainLayout->addWidget(welcomeLabel);
    
    // 查询区域
    QGroupBox* queryGroup = new QGroupBox("快递查询", this);
    QFormLayout* queryLayout = new QFormLayout(queryGroup);
    
    trackingNumberEdit = new QLineEdit(this);
    trackingNumberEdit->setPlaceholderText("输入快递单号");
    
    urgentCheckBox = new QCheckBox("急件", this);
    
    queryButton = new QPushButton("查询位置", this);
    pickupButton = new QPushButton("预约取件", this);
    refreshButton = new QPushButton("刷新列表", this);
    
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(queryButton);
    buttonLayout->addWidget(pickupButton);
    buttonLayout->addWidget(urgentCheckBox);
    buttonLayout->addWidget(refreshButton);
    
    queryLayout->addRow("快递单号:", trackingNumberEdit);
    queryLayout->addRow(buttonLayout);
    
    // 快递表格
    packageTable = new QTableWidget(this);
    packageTable->setColumnCount(5);
    packageTable->setHorizontalHeaderLabels({"快递单号", "货架位置", "状态", "是否急件", "到达时间"});
    packageTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    packageTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    packageTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    // 状态标签
    statusLabel = new QLabel(this);
    statusLabel->setStyleSheet("color: green;");
    
    mainLayout->addWidget(queryGroup);
    mainLayout->addWidget(packageTable);
    mainLayout->addWidget(statusLabel);
    
    setCentralWidget(centralWidget);
    
    // 连接信号槽
    connect(queryButton, &QPushButton::clicked, this, &UserWindow::handlePackageQuery);
    connect(pickupButton, &QPushButton::clicked, this, &UserWindow::handlePickupRequest);
    connect(refreshButton, &QPushButton::clicked, this, &UserWindow::refreshPackageList);
    connect(packageTable, &QTableWidget::cellClicked, this, &UserWindow::showPackageDetails);
}

void UserWindow::handlePackageQuery() {
    QString trackingNumber = trackingNumberEdit->text().trimmed();
    if (trackingNumber.isEmpty()) {
        updateStatusMessage("请输入快递单号", true);
        return;
    }
    
    auto location = pickupService.queryPackageLocation(trackingNumber.toStdString());
    if (location) {
        updateStatusMessage(QString("快递位置: %1").arg(QString::fromStdString(*location)));
    } else {
        updateStatusMessage("未找到该快递", true);
    }
}

void UserWindow::handlePickupRequest() {
    QString trackingNumber = trackingNumberEdit->text().trimmed();
    if (trackingNumber.isEmpty()) {
        updateStatusMessage("请输入快递单号", true);
        return;
    }
    
    bool isUrgent = urgentCheckBox->isChecked();
    bool success = pickupService.schedulePickup(
        trackingNumber.toStdString(), 
        userId.toStdString(), 
        isUrgent);
    
    if (success) {
        updateStatusMessage("取件预约成功");
        refreshPackageList();
    } else {
        updateStatusMessage("取件预约失败", true);
    }
}

void UserWindow::refreshPackageList() {
    loadUserPackages();
    updateStatusMessage("列表已刷新");
}

void UserWindow::showPackageDetails(int row, int) {
    QString trackingNumber = packageTable->item(row, 0)->text();
    trackingNumberEdit->setText(trackingNumber);
}

void UserWindow::loadUserPackages() {
    auto packages = pickupService.getUserPackages(userId.toStdString());
    packageTable->setRowCount(packages.size());
    
    for (int i = 0; i < packages.size(); ++i) {
        const auto& pkg = packages[i];
        
        packageTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(pkg.getTrackingNumber())));
        packageTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(pkg.getShelfNumber())));
        
        QString status = pkg.getPickupTime() == 0 ? "待取件" : "已取件";
        packageTable->setItem(i, 2, new QTableWidgetItem(status));
        
        packageTable->setItem(i, 3, new QTableWidgetItem(pkg.isUrgent() ? "是" : "否"));
        
        char timeStr[20];
        std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M", 
                     std::localtime(&pkg.getArrivalTime()));
        packageTable->setItem(i, 4, new QTableWidgetItem(QString(timeStr)));
    }
}

void UserWindow::updateStatusMessage(const QString& message, bool isError) {
    statusLabel->setText(message);
    statusLabel->setStyleSheet(isError ? "color: red;" : "color: green;");
}