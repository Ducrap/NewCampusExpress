#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QMainWindow>
#include "PickupService.h"
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QLabel>
#include <QCheckBox>
#include <QGroupBox>
#include <ctime>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QPushButton;
class QTableWidget;
class QLabel;
class QCheckBox;
QT_END_NAMESPACE

class UserWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit UserWindow(PickupService& pickupService, const QString& userId, QWidget* parent = nullptr);

private slots:
    void handlePackageQuery();
    void handlePickupRequest();
    void refreshPackageList();
    void showPackageDetails(int row, int column);

private:
    void setupUI();
    void loadUserPackages();
    void updateStatusMessage(const QString& message, bool isError = false);

    PickupService& pickupService;
    QString userId;
    
    // UI Components
    QLineEdit* trackingNumberEdit;
    QCheckBox* urgentCheckBox;
    QPushButton* queryButton;
    QPushButton* pickupButton;
    QPushButton* refreshButton;
    QTableWidget* packageTable;
    QLabel* statusLabel;
    QLabel* welcomeLabel;
};

#endif // USERWINDOW_H