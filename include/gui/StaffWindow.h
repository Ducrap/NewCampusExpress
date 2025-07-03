#ifndef STAFFWINDOW_H
#define STAFFWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include "../staff/StaffService.h"

QT_BEGIN_NAMESPACE
class QLineEdit;
class QPushButton;
class QTableWidget;
class QLabel;
class QComboBox;
class QCheckBox;
QT_END_NAMESPACE

class StaffWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit StaffWindow(StaffService& staffService, QWidget* parent = nullptr);

private slots:
    void handlePackageRegistration();
    void handlePackageUpdate();
    void handlePackageDelete();
    void handleUserRegistration();
    void handleUserUpdate();
    void handleUserDelete();
    void refreshAllTabs();
    void showPackageDetails(int row, int column);
    void showUserDetails(int row, int column);

private:
    void setupPackageTab();
    void setupUserTab();
    void setupStatsTab();
    void loadAllPackages();
    void loadAllUsers();
    void updateStats();
    void updateStatusMessage(const QString& message, bool isError = false);

    StaffService& staffService;
    
    // Main UI Components
    QTabWidget* tabWidget;
    QLabel* statusLabel;
    
    // Package Tab
    QWidget* packageTab;
    QLineEdit* pkgTrackingEdit;
    QLineEdit* pkgPhoneEdit;
    QLineEdit* pkgShelfEdit;
    QCheckBox* pkgUrgentCheck;
    QPushButton* pkgAddButton;
    QPushButton* pkgUpdateButton;
    QPushButton* pkgDeleteButton;
    QPushButton* pkgRefreshButton;
    QTableWidget* pkgTable;
    
    // User Tab
    QWidget* userTab;
    QComboBox* userTypeCombo;
    QLineEdit* userPhoneEdit;
    QLineEdit* userPasswordEdit;
    QLineEdit* userNicknameEdit;
    QPushButton* userAddButton;
    QPushButton* userUpdateButton;
    QPushButton* userDeleteButton;
    QPushButton* userRefreshButton;
    QTableWidget* userTable;
    
    // Statistics Tab
    QWidget* statsTab;
    QLabel* totalPackagesLabel;
    QLabel* urgentPackagesLabel;
    QLabel* pickedUpTodayLabel;
    QLabel* totalUsersLabel;
    QLabel* staffCountLabel;
};

#endif // STAFFWINDOW_H