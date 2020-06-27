/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QLabel *label;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_pwd;
    QLabel *label_password;
    QLineEdit *lineEditPwd;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_signIn;
    QPushButton *pushButton_signUp;
    QPushButton *pushButton;
    QHBoxLayout *horizontalLayout_username;
    QLabel *label_username;
    QLineEdit *lineEditName;

    void setupUi(QDialog *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QString::fromUtf8("Login"));
        Login->resize(355, 282);
        label = new QLabel(Login);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 311, 51));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial Rounded MT Bold"));
        font.setPointSize(14);
        font.setBold(false);
        font.setWeight(50);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        gridLayoutWidget = new QWidget(Login);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(20, 80, 311, 181));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_pwd = new QHBoxLayout();
        horizontalLayout_pwd->setObjectName(QString::fromUtf8("horizontalLayout_pwd"));
        label_password = new QLabel(gridLayoutWidget);
        label_password->setObjectName(QString::fromUtf8("label_password"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Bodoni MT"));
        font1.setPointSize(16);
        label_password->setFont(font1);

        horizontalLayout_pwd->addWidget(label_password);

        lineEditPwd = new QLineEdit(gridLayoutWidget);
        lineEditPwd->setObjectName(QString::fromUtf8("lineEditPwd"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Arial"));
        font2.setPointSize(12);
        lineEditPwd->setFont(font2);

        horizontalLayout_pwd->addWidget(lineEditPwd);


        gridLayout->addLayout(horizontalLayout_pwd, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_signIn = new QPushButton(gridLayoutWidget);
        pushButton_signIn->setObjectName(QString::fromUtf8("pushButton_signIn"));
        pushButton_signIn->setFont(font2);

        horizontalLayout->addWidget(pushButton_signIn);

        pushButton_signUp = new QPushButton(gridLayoutWidget);
        pushButton_signUp->setObjectName(QString::fromUtf8("pushButton_signUp"));
        pushButton_signUp->setFont(font2);

        horizontalLayout->addWidget(pushButton_signUp);

        pushButton = new QPushButton(gridLayoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setFont(font2);

        horizontalLayout->addWidget(pushButton);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 1);

        horizontalLayout_username = new QHBoxLayout();
        horizontalLayout_username->setObjectName(QString::fromUtf8("horizontalLayout_username"));
        label_username = new QLabel(gridLayoutWidget);
        label_username->setObjectName(QString::fromUtf8("label_username"));
        label_username->setFont(font1);

        horizontalLayout_username->addWidget(label_username);

        lineEditName = new QLineEdit(gridLayoutWidget);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));
        lineEditName->setFont(font2);

        horizontalLayout_username->addWidget(lineEditName);


        gridLayout->addLayout(horizontalLayout_username, 0, 0, 1, 1);


        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QDialog *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Login", "WELCOME TO POKEMON GAME", nullptr));
        label_password->setText(QCoreApplication::translate("Login", "password:    ", nullptr));
        pushButton_signIn->setText(QCoreApplication::translate("Login", "Sign In", nullptr));
        pushButton_signUp->setText(QCoreApplication::translate("Login", "Sign Up", nullptr));
        pushButton->setText(QCoreApplication::translate("Login", "Quit", nullptr));
        label_username->setText(QCoreApplication::translate("Login", "username:   ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
