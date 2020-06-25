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

    void createPokemon(QString username, unsigned int create_level);
    void sendPekemon(QDataStream& dsOut, QString user);
    void sendAllUser(unsigned int port);
    void setSql(QString user, Pkm* pokemon);
    void sendOnlineUser(unsigned int port);
    void appendUserFromSql(QString username);
    void updateUserPkm(QDataStream& dsIn, QString username);

private slots:

    void processPendingDatagrams();

//    void on_pushButton_create_clicked();

//    void on_pushButton_levelUp_clicked();

//    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Pokemon *pokemon;

    QSqlDatabase *db;
    QUdpSocket *server;
    QUdpSocket *client;
    unsigned int port;
    unsigned int max_id;
    QList<User*> online_user;   //在线用户
    unsigned int adminPkmNum;
    User* user;

};
#endif // MAINWINDOW_H
