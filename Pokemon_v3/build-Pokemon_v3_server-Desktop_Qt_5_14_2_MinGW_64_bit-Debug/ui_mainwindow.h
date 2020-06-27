/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_pokemon;
    QPushButton *pushButton_user;
    QLabel *label_name;
    QLabel *label_server;
    QLabel *label_title;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(515, 432);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(180, 340, 171, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(11);
        pushButton->setFont(font);
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(100, 110, 321, 191));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Agency FB"));
        font1.setPointSize(24);
        label->setFont(font1);

        verticalLayout->addWidget(label, 0, Qt::AlignHCenter);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_pokemon = new QPushButton(verticalLayoutWidget);
        pushButton_pokemon->setObjectName(QString::fromUtf8("pushButton_pokemon"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Arial"));
        font2.setPointSize(16);
        pushButton_pokemon->setFont(font2);

        horizontalLayout->addWidget(pushButton_pokemon);

        pushButton_user = new QPushButton(verticalLayoutWidget);
        pushButton_user->setObjectName(QString::fromUtf8("pushButton_user"));
        pushButton_user->setFont(font2);

        horizontalLayout->addWidget(pushButton_user);


        verticalLayout->addLayout(horizontalLayout);

        verticalLayout->setStretch(0, 2);
        verticalLayout->setStretch(1, 5);
        label_name = new QLabel(centralwidget);
        label_name->setObjectName(QString::fromUtf8("label_name"));
        label_name->setGeometry(QRect(410, 40, 81, 61));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Arial"));
        font3.setPointSize(12);
        label_name->setFont(font3);
        label_server = new QLabel(centralwidget);
        label_server->setObjectName(QString::fromUtf8("label_server"));
        label_server->setGeometry(QRect(30, 40, 101, 61));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Agency FB"));
        font4.setPointSize(20);
        label_server->setFont(font4);
        label_title = new QLabel(centralwidget);
        label_title->setObjectName(QString::fromUtf8("label_title"));
        label_title->setGeometry(QRect(140, 20, 241, 71));
        QFont font5;
        font5.setFamily(QString::fromUtf8("Arial Rounded MT Bold"));
        font5.setPointSize(32);
        label_title->setFont(font5);
        label_title->setStyleSheet(QString::fromUtf8("background-image: url(:/pokemon.jpg);"));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "STOP SERVER", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "PUSH TO SEE ALL DATA", nullptr));
        pushButton_pokemon->setText(QCoreApplication::translate("MainWindow", "all pokemon", nullptr));
        pushButton_user->setText(QCoreApplication::translate("MainWindow", "all user", nullptr));
        label_name->setText(QCoreApplication::translate("MainWindow", "318-\350\226\233\351\224\246\351\232\206", nullptr));
        label_server->setText(QCoreApplication::translate("MainWindow", "SERVER", nullptr));
        label_title->setText(QCoreApplication::translate("MainWindow", "POKEMON", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
