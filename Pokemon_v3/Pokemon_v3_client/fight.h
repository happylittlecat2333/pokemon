#ifndef FIGHT_H
#define FIGHT_H


#include <QMainWindow>
#include <QtNetwork>
#include <QtSql>
#include <QtTest>
#include <QButtonGroup>
#include <QtDebug>
#include <QListWidgetItem>
#include <QElapsedTimer>

#include "pokemon.h"
#include "high_attack.h"
#include "high_blood.h"
#include "high_defense.h"
#include "high_speed.h"
#include "login.h"
#include "user.h"

class User;
class MainWindow;

namespace Ui {
class Fight;
}

class Fight : public QMainWindow
{
    Q_OBJECT

public:
    explicit Fight(QWidget *parent = 0);
//    explicit Fight(QWidget *parent = 0,unsigned int game_type, User* user, unsigned int userPkmIndex, User* opponent, unsigned int opPkmIndex);

//    void fight();
    void fightBegin(unsigned int game_type, User* user,unsigned int userPkmIndex, User* opponent, unsigned int opPkmIndex);
    bool fightProgress(User* user, unsigned int userPkmIndex, User* opponent, unsigned int opPkmIndex);
    void giveOutPkm(User* user);
    void delay(int time);
    ~Fight();

private slots:
    void on_pushButton_select_clicked();
    void recvData(unsigned int game_type, User* user, unsigned int userPkmIndex, User* opponent, unsigned int opPkmIndex);

signals:
    void setResult();

private:
    Ui::Fight *ui;
    User* user;
    User* opponent;
};

#endif // FIGHT_H
