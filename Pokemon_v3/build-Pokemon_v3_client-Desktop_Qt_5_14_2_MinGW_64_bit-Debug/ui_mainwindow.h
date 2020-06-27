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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label_title;
    QLabel *label_name;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_user_list;
    QLabel *label_allUser;
    QListWidget *listWidget_AllUser;
    QLabel *label;
    QPushButton *pushButton_LogOut;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_main;
    QLabel *label_my_info;
    QLabel *label_opSkill;
    QGridLayout *gridLayout_6;
    QLabel *label_opponent;
    QProgressBar *progressBar_myBlood;
    QLabel *label_myPkmAttr;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_opSel;
    QComboBox *comboBox_opPkm;
    QGridLayout *gridLayout_5;
    QLabel *label_myPic;
    QLabel *label_username;
    QVBoxLayout *verticalLayout;
    QLabel *label_mySkill;
    QHBoxLayout *horizontalLayout;
    QLabel *label_mySel;
    QComboBox *comboBox_myPkm;
    QLabel *label_op_info;
    QProgressBar *progressBar_opBlood;
    QLabel *label_opPic;
    QLabel *label_opPkmAttr;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout_4;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_game_type;
    QLabel *label_gameType;
    QComboBox *comboBox_gameType;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_fight;
    QWidget *gridLayoutWidget_8;
    QGridLayout *gridLayout_user_info;
    QLabel *label_user_badget;
    QLabel *label_user_winRate;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout_giveout;
    QLabel *label_giveOut;
    QComboBox *comboBox_giveOut;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *pushButton_select;
    QPushButton *pushButton;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_button;
    QPushButton *pushButton_allUser;
    QPushButton *pushButton_onlineUser;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1039, 722);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label_title = new QLabel(centralwidget);
        label_title->setObjectName(QString::fromUtf8("label_title"));
        label_title->setGeometry(QRect(270, 0, 211, 71));
        QFont font;
        font.setFamily(QString::fromUtf8("Bauhaus 93"));
        font.setPointSize(32);
        label_title->setFont(font);
        label_title->setStyleSheet(QString::fromUtf8("background-image: url(:/pokemon.jpg);"));
        label_name = new QLabel(centralwidget);
        label_name->setObjectName(QString::fromUtf8("label_name"));
        label_name->setGeometry(QRect(550, 20, 111, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Bahnschrift Light"));
        font1.setPointSize(14);
        label_name->setFont(font1);
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(740, 150, 271, 281));
        verticalLayout_user_list = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_user_list->setObjectName(QString::fromUtf8("verticalLayout_user_list"));
        verticalLayout_user_list->setContentsMargins(0, 0, 0, 0);
        label_allUser = new QLabel(verticalLayoutWidget);
        label_allUser->setObjectName(QString::fromUtf8("label_allUser"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Arial Rounded MT Bold"));
        font2.setPointSize(18);
        label_allUser->setFont(font2);

        verticalLayout_user_list->addWidget(label_allUser, 0, Qt::AlignHCenter);

        listWidget_AllUser = new QListWidget(verticalLayoutWidget);
        listWidget_AllUser->setObjectName(QString::fromUtf8("listWidget_AllUser"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Arial Rounded MT Bold"));
        font3.setPointSize(12);
        listWidget_AllUser->setFont(font3);

        verticalLayout_user_list->addWidget(listWidget_AllUser);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(110, 30, 91, 31));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Agency FB"));
        font4.setPointSize(20);
        label->setFont(font4);
        pushButton_LogOut = new QPushButton(centralwidget);
        pushButton_LogOut->setObjectName(QString::fromUtf8("pushButton_LogOut"));
        pushButton_LogOut->setGeometry(QRect(850, 620, 141, 32));
        QFont font5;
        font5.setFamily(QString::fromUtf8("Arial"));
        font5.setPointSize(10);
        pushButton_LogOut->setFont(font5);
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(90, 80, 571, 491));
        gridLayout_main = new QGridLayout(gridLayoutWidget);
        gridLayout_main->setObjectName(QString::fromUtf8("gridLayout_main"));
        gridLayout_main->setContentsMargins(0, 0, 0, 0);
        label_my_info = new QLabel(gridLayoutWidget);
        label_my_info->setObjectName(QString::fromUtf8("label_my_info"));

        gridLayout_main->addWidget(label_my_info, 3, 0, 1, 1);

        label_opSkill = new QLabel(gridLayoutWidget);
        label_opSkill->setObjectName(QString::fromUtf8("label_opSkill"));
        QFont font6;
        font6.setFamily(QString::fromUtf8("Chiller"));
        font6.setPointSize(24);
        label_opSkill->setFont(font6);

        gridLayout_main->addWidget(label_opSkill, 15, 3, 1, 1);

        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));

        gridLayout_main->addLayout(gridLayout_6, 7, 1, 1, 1);

        label_opponent = new QLabel(gridLayoutWidget);
        label_opponent->setObjectName(QString::fromUtf8("label_opponent"));
        label_opponent->setFont(font2);

        gridLayout_main->addWidget(label_opponent, 1, 3, 1, 1);

        progressBar_myBlood = new QProgressBar(gridLayoutWidget);
        progressBar_myBlood->setObjectName(QString::fromUtf8("progressBar_myBlood"));
        progressBar_myBlood->setValue(24);

        gridLayout_main->addWidget(progressBar_myBlood, 14, 0, 1, 1);

        label_myPkmAttr = new QLabel(gridLayoutWidget);
        label_myPkmAttr->setObjectName(QString::fromUtf8("label_myPkmAttr"));
        label_myPkmAttr->setFont(font1);

        gridLayout_main->addWidget(label_myPkmAttr, 5, 0, 2, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_opSel = new QLabel(gridLayoutWidget);
        label_opSel->setObjectName(QString::fromUtf8("label_opSel"));
        QFont font7;
        font7.setFamily(QString::fromUtf8("Agency FB"));
        font7.setPointSize(16);
        label_opSel->setFont(font7);

        horizontalLayout_2->addWidget(label_opSel);

        comboBox_opPkm = new QComboBox(gridLayoutWidget);
        comboBox_opPkm->setObjectName(QString::fromUtf8("comboBox_opPkm"));
        QFont font8;
        font8.setFamily(QString::fromUtf8("Arial Narrow"));
        font8.setPointSize(12);
        comboBox_opPkm->setFont(font8);

        horizontalLayout_2->addWidget(comboBox_opPkm);


        gridLayout_main->addLayout(horizontalLayout_2, 4, 3, 1, 1);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));

        gridLayout_main->addLayout(gridLayout_5, 7, 2, 1, 1);

        label_myPic = new QLabel(gridLayoutWidget);
        label_myPic->setObjectName(QString::fromUtf8("label_myPic"));
        QFont font9;
        font9.setPointSize(16);
        label_myPic->setFont(font9);
        label_myPic->setStyleSheet(QString::fromUtf8(""));

        gridLayout_main->addWidget(label_myPic, 7, 0, 7, 1);

        label_username = new QLabel(gridLayoutWidget);
        label_username->setObjectName(QString::fromUtf8("label_username"));
        label_username->setFont(font2);

        gridLayout_main->addWidget(label_username, 1, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

        gridLayout_main->addLayout(verticalLayout, 12, 2, 1, 1);

        label_mySkill = new QLabel(gridLayoutWidget);
        label_mySkill->setObjectName(QString::fromUtf8("label_mySkill"));
        label_mySkill->setFont(font6);

        gridLayout_main->addWidget(label_mySkill, 15, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_mySel = new QLabel(gridLayoutWidget);
        label_mySel->setObjectName(QString::fromUtf8("label_mySel"));
        label_mySel->setFont(font7);

        horizontalLayout->addWidget(label_mySel);

        comboBox_myPkm = new QComboBox(gridLayoutWidget);
        comboBox_myPkm->setObjectName(QString::fromUtf8("comboBox_myPkm"));
        comboBox_myPkm->setFont(font8);

        horizontalLayout->addWidget(comboBox_myPkm);


        gridLayout_main->addLayout(horizontalLayout, 4, 0, 1, 1);

        label_op_info = new QLabel(gridLayoutWidget);
        label_op_info->setObjectName(QString::fromUtf8("label_op_info"));

        gridLayout_main->addWidget(label_op_info, 3, 3, 1, 1);

        progressBar_opBlood = new QProgressBar(gridLayoutWidget);
        progressBar_opBlood->setObjectName(QString::fromUtf8("progressBar_opBlood"));
        progressBar_opBlood->setValue(24);

        gridLayout_main->addWidget(progressBar_opBlood, 14, 3, 1, 1);

        label_opPic = new QLabel(gridLayoutWidget);
        label_opPic->setObjectName(QString::fromUtf8("label_opPic"));
        label_opPic->setFont(font9);

        gridLayout_main->addWidget(label_opPic, 7, 3, 7, 1);

        label_opPkmAttr = new QLabel(gridLayoutWidget);
        label_opPkmAttr->setObjectName(QString::fromUtf8("label_opPkmAttr"));
        label_opPkmAttr->setFont(font1);

        gridLayout_main->addWidget(label_opPkmAttr, 5, 3, 2, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));

        gridLayout_main->addLayout(gridLayout_3, 11, 2, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));

        gridLayout_main->addLayout(gridLayout_2, 13, 2, 1, 1);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));

        gridLayout_main->addLayout(gridLayout_4, 10, 2, 1, 1);

        horizontalLayoutWidget_3 = new QWidget(centralwidget);
        horizontalLayoutWidget_3->setObjectName(QString::fromUtf8("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(90, 570, 571, 51));
        horizontalLayout_game_type = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_game_type->setObjectName(QString::fromUtf8("horizontalLayout_game_type"));
        horizontalLayout_game_type->setContentsMargins(0, 0, 0, 0);
        label_gameType = new QLabel(horizontalLayoutWidget_3);
        label_gameType->setObjectName(QString::fromUtf8("label_gameType"));
        QFont font10;
        font10.setFamily(QString::fromUtf8("Baskerville Old Face"));
        font10.setPointSize(14);
        label_gameType->setFont(font10);

        horizontalLayout_game_type->addWidget(label_gameType);

        comboBox_gameType = new QComboBox(horizontalLayoutWidget_3);
        comboBox_gameType->setObjectName(QString::fromUtf8("comboBox_gameType"));
        comboBox_gameType->setFont(font8);

        horizontalLayout_game_type->addWidget(comboBox_gameType);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));

        horizontalLayout_game_type->addLayout(horizontalLayout_4);

        pushButton_fight = new QPushButton(horizontalLayoutWidget_3);
        pushButton_fight->setObjectName(QString::fromUtf8("pushButton_fight"));
        QFont font11;
        font11.setFamily(QString::fromUtf8("Arial"));
        font11.setPointSize(11);
        font11.setBold(false);
        font11.setWeight(50);
        pushButton_fight->setFont(font11);

        horizontalLayout_game_type->addWidget(pushButton_fight);

        gridLayoutWidget_8 = new QWidget(centralwidget);
        gridLayoutWidget_8->setObjectName(QString::fromUtf8("gridLayoutWidget_8"));
        gridLayoutWidget_8->setGeometry(QRect(740, 440, 271, 161));
        gridLayout_user_info = new QGridLayout(gridLayoutWidget_8);
        gridLayout_user_info->setObjectName(QString::fromUtf8("gridLayout_user_info"));
        gridLayout_user_info->setContentsMargins(0, 0, 0, 0);
        label_user_badget = new QLabel(gridLayoutWidget_8);
        label_user_badget->setObjectName(QString::fromUtf8("label_user_badget"));
        QFont font12;
        font12.setFamily(QString::fromUtf8("Agency FB"));
        font12.setPointSize(14);
        label_user_badget->setFont(font12);

        gridLayout_user_info->addWidget(label_user_badget, 2, 0, 1, 1);

        label_user_winRate = new QLabel(gridLayoutWidget_8);
        label_user_winRate->setObjectName(QString::fromUtf8("label_user_winRate"));
        label_user_winRate->setFont(font12);

        gridLayout_user_info->addWidget(label_user_winRate, 1, 0, 1, 1);

        horizontalLayoutWidget_4 = new QWidget(centralwidget);
        horizontalLayoutWidget_4->setObjectName(QString::fromUtf8("horizontalLayoutWidget_4"));
        horizontalLayoutWidget_4->setGeometry(QRect(150, 620, 431, 61));
        horizontalLayout_giveout = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout_giveout->setObjectName(QString::fromUtf8("horizontalLayout_giveout"));
        horizontalLayout_giveout->setContentsMargins(0, 0, 0, 0);
        label_giveOut = new QLabel(horizontalLayoutWidget_4);
        label_giveOut->setObjectName(QString::fromUtf8("label_giveOut"));
        QFont font13;
        font13.setFamily(QString::fromUtf8("Bell MT"));
        font13.setPointSize(14);
        label_giveOut->setFont(font13);

        horizontalLayout_giveout->addWidget(label_giveOut);

        comboBox_giveOut = new QComboBox(horizontalLayoutWidget_4);
        comboBox_giveOut->setObjectName(QString::fromUtf8("comboBox_giveOut"));
        comboBox_giveOut->setFont(font8);

        horizontalLayout_giveout->addWidget(comboBox_giveOut);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));

        horizontalLayout_giveout->addLayout(horizontalLayout_6);

        pushButton_select = new QPushButton(horizontalLayoutWidget_4);
        pushButton_select->setObjectName(QString::fromUtf8("pushButton_select"));
        QFont font14;
        font14.setFamily(QString::fromUtf8("Arial"));
        font14.setPointSize(12);
        pushButton_select->setFont(font14);

        horizontalLayout_giveout->addWidget(pushButton_select);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(710, 620, 121, 32));
        pushButton->setFont(font5);
        gridLayoutWidget_2 = new QWidget(centralwidget);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(760, 10, 221, 131));
        gridLayout_button = new QGridLayout(gridLayoutWidget_2);
        gridLayout_button->setObjectName(QString::fromUtf8("gridLayout_button"));
        gridLayout_button->setHorizontalSpacing(6);
        gridLayout_button->setVerticalSpacing(9);
        gridLayout_button->setContentsMargins(0, 0, 0, 0);
        pushButton_allUser = new QPushButton(gridLayoutWidget_2);
        pushButton_allUser->setObjectName(QString::fromUtf8("pushButton_allUser"));
        pushButton_allUser->setFont(font5);

        gridLayout_button->addWidget(pushButton_allUser, 0, 0, 1, 1);

        pushButton_onlineUser = new QPushButton(gridLayoutWidget_2);
        pushButton_onlineUser->setObjectName(QString::fromUtf8("pushButton_onlineUser"));
        pushButton_onlineUser->setFont(font5);

        gridLayout_button->addWidget(pushButton_onlineUser, 1, 0, 1, 1);

        gridLayout_button->setRowStretch(1, 1);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1039, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_title->setText(QCoreApplication::translate("MainWindow", "POKEMON", nullptr));
        label_name->setText(QCoreApplication::translate("MainWindow", "318-\350\226\233\351\224\246\351\232\206", nullptr));
        label_allUser->setText(QCoreApplication::translate("MainWindow", "All User", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "CLIENT", nullptr));
        pushButton_LogOut->setText(QCoreApplication::translate("MainWindow", "log out", nullptr));
        label_my_info->setText(QString());
        label_opSkill->setText(QString());
        label_opponent->setText(QCoreApplication::translate("MainWindow", "Opponent", nullptr));
        label_myPkmAttr->setText(QCoreApplication::translate("MainWindow", "None", nullptr));
        label_opSel->setText(QCoreApplication::translate("MainWindow", "select Pokemon:", nullptr));
        label_myPic->setText(QString());
        label_username->setText(QCoreApplication::translate("MainWindow", "Username", nullptr));
        label_mySkill->setText(QString());
        label_mySel->setText(QCoreApplication::translate("MainWindow", "selecet Pokemon:", nullptr));
        label_op_info->setText(QString());
        label_opPic->setText(QString());
        label_opPkmAttr->setText(QCoreApplication::translate("MainWindow", "None", nullptr));
        label_gameType->setText(QCoreApplication::translate("MainWindow", "game type:", nullptr));
        pushButton_fight->setText(QCoreApplication::translate("MainWindow", "Fight", nullptr));
        label_user_badget->setText(QCoreApplication::translate("MainWindow", "And Badget info", nullptr));
        label_user_winRate->setText(QCoreApplication::translate("MainWindow", "Press all user to show User's info", nullptr));
        label_giveOut->setText(QCoreApplication::translate("MainWindow", "choose on to give:", nullptr));
        pushButton_select->setText(QCoreApplication::translate("MainWindow", "Select", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "add experience", nullptr));
        pushButton_allUser->setText(QCoreApplication::translate("MainWindow", "all user", nullptr));
        pushButton_onlineUser->setText(QCoreApplication::translate("MainWindow", "online user", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
