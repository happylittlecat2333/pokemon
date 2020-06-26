#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QtNetwork>
#include <QtSql>
#include <QtTest>
#include <QtDebug>
#include <QMessageBox>

#include "mainwindow.h"
#include "pokemon.h"
#include "high_attack.h"
#include "high_blood.h"
#include "high_defense.h"
#include "high_speed.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    void setAttrAll(QDataStream& dsIn, unsigned int num);
    Pkm **getAllPkm(){return attrAll;};
    QString getUsername(){return username;};
    unsigned int getPkmNum(){return pkmNum;};
    ~Login();
    unsigned int win;
    unsigned int lose;

private slots:
    void processPendingDatagrams();

    void on_pushButton_signIn_clicked();

    void on_pushButton_signUp_clicked();

    void on_pushButton_clicked();

private:
    Ui::Login *ui;

    QUdpSocket *server;
    QUdpSocket *client;

    QString username;
    Pkm *attrAll[20];
    unsigned int port;
    unsigned int pkmNum=0;


};

#endif // LOGIN_H
