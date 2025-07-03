/********************************************************************************
** Form generated from reading UI file 'UserWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERWINDOW_H
#define UI_USERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QLabel *welcomeLabel;
    QGroupBox *queryGroup;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *trackingNumberEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *queryButton;
    QPushButton *pickupButton;
    QCheckBox *urgentCheckBox;
    QTableWidget *packageTable;

    void setupUi(QMainWindow *UserWindow)
    {
        if (UserWindow->objectName().isEmpty())
            UserWindow->setObjectName("UserWindow");
        UserWindow->resize(800, 600);
        centralWidget = new QWidget(UserWindow);
        centralWidget->setObjectName("centralWidget");
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setObjectName("verticalLayout");
        welcomeLabel = new QLabel(centralWidget);
        welcomeLabel->setObjectName("welcomeLabel");
        welcomeLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(welcomeLabel);

        queryGroup = new QGroupBox(centralWidget);
        queryGroup->setObjectName("queryGroup");
        verticalLayout_2 = new QVBoxLayout(queryGroup);
        verticalLayout_2->setObjectName("verticalLayout_2");
        trackingNumberEdit = new QLineEdit(queryGroup);
        trackingNumberEdit->setObjectName("trackingNumberEdit");

        verticalLayout_2->addWidget(trackingNumberEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        queryButton = new QPushButton(queryGroup);
        queryButton->setObjectName("queryButton");

        horizontalLayout->addWidget(queryButton);

        pickupButton = new QPushButton(queryGroup);
        pickupButton->setObjectName("pickupButton");

        horizontalLayout->addWidget(pickupButton);

        urgentCheckBox = new QCheckBox(queryGroup);
        urgentCheckBox->setObjectName("urgentCheckBox");

        horizontalLayout->addWidget(urgentCheckBox);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout->addWidget(queryGroup);

        packageTable = new QTableWidget(centralWidget);
        if (packageTable->columnCount() < 5)
            packageTable->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        packageTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        packageTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        packageTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        packageTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        packageTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        packageTable->setObjectName("packageTable");

        verticalLayout->addWidget(packageTable);

        UserWindow->setCentralWidget(centralWidget);

        retranslateUi(UserWindow);

        QMetaObject::connectSlotsByName(UserWindow);
    } // setupUi

    void retranslateUi(QMainWindow *UserWindow)
    {
        UserWindow->setWindowTitle(QCoreApplication::translate("UserWindow", "\346\240\241\345\233\255\345\277\253\351\200\222\351\251\277\347\253\231 - \347\224\250\346\210\267\347\225\214\351\235\242", nullptr));
        welcomeLabel->setText(QCoreApplication::translate("UserWindow", "\346\254\242\350\277\216\346\202\250\357\274\214\347\224\250\346\210\267", nullptr));
        queryGroup->setTitle(QCoreApplication::translate("UserWindow", "\345\277\253\351\200\222\346\237\245\350\257\242", nullptr));
        trackingNumberEdit->setPlaceholderText(QCoreApplication::translate("UserWindow", "\350\276\223\345\205\245\345\277\253\351\200\222\345\215\225\345\217\267", nullptr));
        queryButton->setText(QCoreApplication::translate("UserWindow", "\346\237\245\350\257\242\344\275\215\347\275\256", nullptr));
        pickupButton->setText(QCoreApplication::translate("UserWindow", "\351\242\204\347\272\246\345\217\226\344\273\266", nullptr));
        urgentCheckBox->setText(QCoreApplication::translate("UserWindow", "\346\200\245\344\273\266", nullptr));
        QTableWidgetItem *___qtablewidgetitem = packageTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("UserWindow", "\345\277\253\351\200\222\345\215\225\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = packageTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("UserWindow", "\350\264\247\346\236\266\344\275\215\347\275\256", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = packageTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("UserWindow", "\347\212\266\346\200\201", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = packageTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("UserWindow", "\346\230\257\345\220\246\346\200\245\344\273\266", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = packageTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("UserWindow", "\345\210\260\350\276\276\346\227\266\351\227\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserWindow: public Ui_UserWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERWINDOW_H
