/********************************************************************************
** Form generated from reading UI file 'LoginWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QComboBox *userTypeCombo;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QPushButton *loginButton;
    QPushButton *registerButton;

    void setupUi(QMainWindow *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName("LoginWindow");
        LoginWindow->resize(400, 300);
        centralWidget = new QWidget(LoginWindow);
        centralWidget->setObjectName("centralWidget");
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setObjectName("verticalLayout");
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName("groupBox");
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName("verticalLayout_2");
        userTypeCombo = new QComboBox(groupBox);
        userTypeCombo->addItem(QString());
        userTypeCombo->addItem(QString());
        userTypeCombo->setObjectName("userTypeCombo");

        verticalLayout_2->addWidget(userTypeCombo);

        usernameEdit = new QLineEdit(groupBox);
        usernameEdit->setObjectName("usernameEdit");

        verticalLayout_2->addWidget(usernameEdit);

        passwordEdit = new QLineEdit(groupBox);
        passwordEdit->setObjectName("passwordEdit");
        passwordEdit->setEchoMode(QLineEdit::Password);

        verticalLayout_2->addWidget(passwordEdit);

        loginButton = new QPushButton(groupBox);
        loginButton->setObjectName("loginButton");

        verticalLayout_2->addWidget(loginButton);

        registerButton = new QPushButton(groupBox);
        registerButton->setObjectName("registerButton");

        verticalLayout_2->addWidget(registerButton);


        verticalLayout->addWidget(groupBox);

        LoginWindow->setCentralWidget(centralWidget);

        retranslateUi(LoginWindow);

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QMainWindow *LoginWindow)
    {
        LoginWindow->setWindowTitle(QCoreApplication::translate("LoginWindow", "\346\240\241\345\233\255\345\277\253\351\200\222\351\251\277\347\253\231 - \347\231\273\345\275\225", nullptr));
        groupBox->setTitle(QCoreApplication::translate("LoginWindow", "\347\224\250\346\210\267\347\231\273\345\275\225", nullptr));
        userTypeCombo->setItemText(0, QCoreApplication::translate("LoginWindow", "\345\255\246\347\224\237\347\224\250\346\210\267", nullptr));
        userTypeCombo->setItemText(1, QCoreApplication::translate("LoginWindow", "\345\267\245\344\275\234\344\272\272\345\221\230", nullptr));

        usernameEdit->setPlaceholderText(QCoreApplication::translate("LoginWindow", "\350\276\223\345\205\245\346\211\213\346\234\272\345\217\267\346\210\226\347\224\250\346\210\267ID", nullptr));
        passwordEdit->setPlaceholderText(QCoreApplication::translate("LoginWindow", "\350\276\223\345\205\245\345\257\206\347\240\201", nullptr));
        loginButton->setText(QCoreApplication::translate("LoginWindow", "\347\231\273\345\275\225", nullptr));
        registerButton->setText(QCoreApplication::translate("LoginWindow", "\346\263\250\345\206\214\346\226\260\350\264\246\345\217\267", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
