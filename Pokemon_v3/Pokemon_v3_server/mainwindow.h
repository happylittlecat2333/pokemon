#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QtSql>
#include <QtTest>
#include <QtDebug>
#include <QTableView>
#include <QFileDialog>
#include <QtSql>
#include <QSqlTableModel>

#include "pokemon.h"
#include "high_attack.h"
#include "high_blood.h"
#include "high_defense.h"
#include "high_speed.h"
#include "user.h"

enum LOG_TYPE  {SIGN_IN, SIGN_UP, NAME_EXIST, SIGN_UP_SUCCESS, USER_NONE, PWD_ERROR, SIGN_IN_SUCESS, SIGN_OUT, ALL_USER, ONLINE_USER,VIRTUAL_PKM, PKM_DATA};
//不同的发送的种类

class User;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void createPokemon(QString username, unsigned int create_level);    //生成pokemon，写入pokemon数据库
    void sendPekemon(QDataStream& dsOut, QString user); //发送user的所有pokemon的信息
    void sendAllUser(unsigned int port);    //从数据库返回所有用户信息（用户名，所有精灵）
    void setSql(QString user, Pkm* pokemon);    //设置pokemon数据库的内容
    void sendOnlineUser(unsigned int port);     //从online_user中返回数据
    void appendUserFromSql(QString username);   //在线用户增加，新增一个online_user
    void updateUserPkm(QDataStream& dsIn, QString username);     //更新用户在数据库的所有pokemon信息

private slots:

    void processPendingDatagrams(); //处理传来的数据

    void on_pushButton_clicked();

    void on_pushButton_pokemon_clicked();   //显示数据库中所有pokemon

    void on_pushButton_user_clicked();  //显示数据库中所有user

private:
    Ui::MainWindow *ui;
    Pokemon *pokemon;

    QSqlDatabase *db;
    QUdpSocket *server;
    QUdpSocket *client;
    unsigned int port;
    unsigned int max_id;    //pokemon表的条数
    QList<User*> online_user;   //在线用户
    unsigned int adminPkmNum;   //主机虚拟精灵的个数
    User* user;

};
#endif // MAINWINDOW_H
