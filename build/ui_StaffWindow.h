/********************************************************************************
** Form generated from reading UI file 'StaffWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STAFFWINDOW_H
#define UI_STAFFWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StaffWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *packageTab;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *packageGroup;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *pkgTrackingEdit;
    QLabel *label_2;
    QLineEdit *pkgPhoneEdit;
    QLabel *label_3;
    QLineEdit *pkgShelfEdit;
    QCheckBox *pkgUrgentCheck;
    QHBoxLayout *horizontalLayout;
    QPushButton *pkgAddButton;
    QPushButton *pkgUpdateButton;
    QPushButton *pkgDeleteButton;
    QTableWidget *pkgTable;
    QWidget *userTab;
    QWidget *statsTab;

    void setupUi(QMainWindow *StaffWindow)
    {
        if (StaffWindow->objectName().isEmpty())
            StaffWindow->setObjectName("StaffWindow");
        StaffWindow->resize(1000, 700);
        centralWidget = new QWidget(StaffWindow);
        centralWidget->setObjectName("centralWidget");
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setObjectName("verticalLayout");
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName("tabWidget");
        packageTab = new QWidget();
        packageTab->setObjectName("packageTab");
        verticalLayout_2 = new QVBoxLayout(packageTab);
        verticalLayout_2->setObjectName("verticalLayout_2");
        packageGroup = new QGroupBox(packageTab);
        packageGroup->setObjectName("packageGroup");
        formLayout = new QFormLayout(packageGroup);
        formLayout->setObjectName("formLayout");
        label = new QLabel(packageGroup);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label);

        pkgTrackingEdit = new QLineEdit(packageGroup);
        pkgTrackingEdit->setObjectName("pkgTrackingEdit");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, pkgTrackingEdit);

        label_2 = new QLabel(packageGroup);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_2);

        pkgPhoneEdit = new QLineEdit(packageGroup);
        pkgPhoneEdit->setObjectName("pkgPhoneEdit");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, pkgPhoneEdit);

        label_3 = new QLabel(packageGroup);
        label_3->setObjectName("label_3");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, label_3);

        pkgShelfEdit = new QLineEdit(packageGroup);
        pkgShelfEdit->setObjectName("pkgShelfEdit");

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, pkgShelfEdit);

        pkgUrgentCheck = new QCheckBox(packageGroup);
        pkgUrgentCheck->setObjectName("pkgUrgentCheck");

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, pkgUrgentCheck);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        pkgAddButton = new QPushButton(packageGroup);
        pkgAddButton->setObjectName("pkgAddButton");

        horizontalLayout->addWidget(pkgAddButton);

        pkgUpdateButton = new QPushButton(packageGroup);
        pkgUpdateButton->setObjectName("pkgUpdateButton");

        horizontalLayout->addWidget(pkgUpdateButton);

        pkgDeleteButton = new QPushButton(packageGroup);
        pkgDeleteButton->setObjectName("pkgDeleteButton");

        horizontalLayout->addWidget(pkgDeleteButton);


        formLayout->setLayout(4, QFormLayout::ItemRole::SpanningRole, horizontalLayout);


        verticalLayout_2->addWidget(packageGroup);

        pkgTable = new QTableWidget(packageTab);
        if (pkgTable->columnCount() < 6)
            pkgTable->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        pkgTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        pkgTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        pkgTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        pkgTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        pkgTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        pkgTable->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        pkgTable->setObjectName("pkgTable");

        verticalLayout_2->addWidget(pkgTable);

        tabWidget->addTab(packageTab, QString());
        userTab = new QWidget();
        userTab->setObjectName("userTab");
        tabWidget->addTab(userTab, QString());
        statsTab = new QWidget();
        statsTab->setObjectName("statsTab");
        tabWidget->addTab(statsTab, QString());

        verticalLayout->addWidget(tabWidget);

        StaffWindow->setCentralWidget(centralWidget);

        retranslateUi(StaffWindow);

        QMetaObject::connectSlotsByName(StaffWindow);
    } // setupUi

    void retranslateUi(QMainWindow *StaffWindow)
    {
        StaffWindow->setWindowTitle(QCoreApplication::translate("StaffWindow", "\346\240\241\345\233\255\345\277\253\351\200\222\351\251\277\347\253\231 - \345\267\245\344\275\234\344\272\272\345\221\230\347\225\214\351\235\242", nullptr));
        packageGroup->setTitle(QCoreApplication::translate("StaffWindow", "\345\277\253\351\200\222\346\223\215\344\275\234", nullptr));
        label->setText(QCoreApplication::translate("StaffWindow", "\345\277\253\351\200\222\345\215\225\345\217\267:", nullptr));
        label_2->setText(QCoreApplication::translate("StaffWindow", "\346\224\266\344\273\266\344\272\272\346\211\213\346\234\272:", nullptr));
        label_3->setText(QCoreApplication::translate("StaffWindow", "\350\264\247\346\236\266\344\275\215\347\275\256:", nullptr));
        pkgUrgentCheck->setText(QCoreApplication::translate("StaffWindow", "\346\200\245\344\273\266", nullptr));
        pkgAddButton->setText(QCoreApplication::translate("StaffWindow", "\346\267\273\345\212\240\345\277\253\351\200\222", nullptr));
        pkgUpdateButton->setText(QCoreApplication::translate("StaffWindow", "\346\233\264\346\226\260\344\277\241\346\201\257", nullptr));
        pkgDeleteButton->setText(QCoreApplication::translate("StaffWindow", "\345\210\240\351\231\244\345\277\253\351\200\222", nullptr));
        QTableWidgetItem *___qtablewidgetitem = pkgTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("StaffWindow", "\345\277\253\351\200\222\345\215\225\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = pkgTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("StaffWindow", "\346\224\266\344\273\266\344\272\272", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = pkgTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("StaffWindow", "\350\264\247\346\236\266\344\275\215\347\275\256", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = pkgTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("StaffWindow", "\346\230\257\345\220\246\346\200\245\344\273\266", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = pkgTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("StaffWindow", "\347\212\266\346\200\201", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = pkgTable->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("StaffWindow", "\345\210\260\350\276\276\346\227\266\351\227\264", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(packageTab), QCoreApplication::translate("StaffWindow", "\345\277\253\351\200\222\347\256\241\347\220\206", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(userTab), QCoreApplication::translate("StaffWindow", "\347\224\250\346\210\267\347\256\241\347\220\206", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(statsTab), QCoreApplication::translate("StaffWindow", "\347\263\273\347\273\237\347\273\237\350\256\241", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StaffWindow: public Ui_StaffWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STAFFWINDOW_H
