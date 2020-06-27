#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QtSql>
#include <QtTest>
#include <QButtonGroup>
#include <QtDebug>
#include <QListWidgetItem>


#include "pokemon.h"
#include "high_attack.h"
#include "high_blood.h"
#include "high_defense.h"
#include "high_speed.h"
#include "login.h"
#include "user.h"

enum LOG_TYPE  {SIGN_IN, SIGN_UP, NAME_EXIST, SIGN_UP_SUCCESS, USER_NONE, PWD_ERROR, SIGN_IN_SUCESS, SIGN_OUT, ALL_USER, ONLINE_USER, VIRTUAL_PKM, PKM_DATA};
//不同的发送的种类
enum MODE {MY_PKM, USER_PKM};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Login;
class User;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, Login *login = 0);
    ~MainWindow();

    QString getPkmAttr(unsigned int num);   //根据不同mode模式，返回pokemon信息(用于设置Text中的内容，为QString类型)
    void setComboBoxValue(unsigned int Is_my_pkm); //设置用户或admin的所有信息（combobox、label）
    void updateUserPkm();   //在server端数据库中，更新user自己的pokemon信息
    void showGameType();    //展示主界面
    void hideGameType();    //进入对战模式，切换对战界面
    void showGiveOut();     //决斗赛中，展示选择要送出的pokemon
    void hideGiveOut();     //隐藏决斗赛中，送出pokemon界面
    void fightBegin(unsigned int game_type, User* user, unsigned int userPkmIndex, User* opponent, unsigned int opPkmIndex); //开始比赛
    bool fightProgress(User* user, unsigned int userPkmIndex, User* opponent, unsigned int opPkmIndex); //比赛过程
    void giveOutPkm(User *user);    //送出一个pokemon
    void delay(int time);   //模拟真实攻击间隔

private slots:

    void processPendingDatagrams(); //处理传来的数据

    void on_listWidget_AllUser_currentRowChanged(int currentRow); //在所有用户中选中其中一个用户，展示用户信息

    void on_pushButton_allUser_clicked(); //根据所有用户Users，设置listWidget

    void on_pushButton_onlineUser_clicked(); //根据所有在线用户online_user，设置listWidget

    void on_pushButton_LogOut_clicked(); //登出

    void on_comboBox_opPkm_currentIndexChanged(int index);  //更新显示主机admin的pokemon信息

    void on_comboBox_myPkm_currentIndexChanged(int index);  //更新显示用户的pokemon信息

    void on_comboBox_gameType_currentIndexChanged(int index);  //选择游戏类型

    void on_pushButton_fight_clicked(); //进入比赛界面，开始比赛

    void on_pushButton_select_clicked();    //决定要送出的pokemon

    void on_pushButton_clicked();   //快速升级

    void on_comboBox_giveOut_currentIndexChanged(int index);    //展示所有可能送出的pokemon

private:
    Ui::MainWindow *ui;
    Pokemon *pokemon;
    Pkm **allPkmAttr;   //用户的所有pokemon信息，用于界面之间的数据交换
    QList<User*> Users;  //所有用户的信息
    QList<User*> online_user;   //所有在线用户的信息
    User* admin;    //主机信息
    User* user;
    unsigned int mode;  //不同展示模式

    QSqlDatabase *db;
    QUdpSocket *server;
    QUdpSocket *client;

    QString username;   //用户名
    unsigned int port;

    unsigned int pkmNum;    //用户pokemon个数
    unsigned int game_type;
    unsigned int selectedIndex;

};
#endif // MAINWINDOW_H
