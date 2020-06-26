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
#include "fight.h"

enum LOG_TYPE  {SIGN_IN, SIGN_UP, NAME_EXIST, SIGN_UP_SUCCESS, USER_NONE, PWD_ERROR, SIGN_IN_SUCESS, SIGN_OUT, ALL_USER, ONLINE_USER, VIRTUAL_PKM, PKM_DATA};
enum MODE {MY_PKM, USER_PKM};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Login;
class User;
class Fight;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, Login *login = 0);
    ~MainWindow();

    void createPokemon(QString username);
    void sendPekemon(QDataStream& dsOut, QString user);
    void sendAllUser(unsigned int port);
    void setSql(QString user, Pkm* pokemon);
    void getVirtualPkm(QDataStream& dsIn);
    QString getPkmAttr(unsigned int num);
    void setComboBoxValue(unsigned int Is_my_pkm);
    void updateUserPkm();
    void showGameType();
    void hideGameType();
    void showGiveOut();
    void hideGiveOut();
    void fightBegin(unsigned int game_type, User* user, unsigned int userPkmIndex, User* opponent, unsigned int opPkmIndex);
    bool fightProgress(User* user, unsigned int userPkmIndex, User* opponent, unsigned int opPkmIndex);
    void giveOutPkm(User *user);
    void delay(int time);

signals:
    void sendData(unsigned int game_type, User* user, unsigned int userPkmIndex, User* opponent, unsigned int opPkmIndex);

private slots:

    void processPendingDatagrams();

//    void on_pushButton_create_clicked();

//    void on_pushButton_levelUp_clicked();

    void on_listWidget_AllUser_currentRowChanged(int currentRow);


    void RecvPkmID(int);

    void on_pushButton_allUser_clicked();

//    void on_pushButton_myPkm_clicked();

    void on_pushButton_onlineUser_clicked();

    void on_pushButton_LogOut_clicked();

    void on_comboBox_opPkm_currentIndexChanged(int index);

    void on_comboBox_myPkm_currentIndexChanged(int index);

    void on_comboBox_gameType_currentIndexChanged(int index);

    void on_pushButton_fight_clicked();

    void recResult();



    void on_pushButton_select_clicked();

    void on_pushButton_clicked();

    void on_comboBox_giveOut_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    Pokemon *pokemon;
    Pkm **allPkmAttr;   //自己的pkm所有属性
    QList<User*> Users;  //所有人的pkm属性
    QList<User*> online_user;
    QList<Pkm*> virtual_pkm;
    User* admin;
    User* user;
    unsigned int mode;

    QSqlDatabase *db;
    QUdpSocket *server;
    QUdpSocket *client;

    QString username;
    unsigned int port;
    QButtonGroup *button_group;
    Fight *fight;

    unsigned int pkmNum;
    unsigned int game_type;
    unsigned int selectedIndex;

};
#endif // MAINWINDOW_H
