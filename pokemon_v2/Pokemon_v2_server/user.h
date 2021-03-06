#ifndef USER_H
#define USER_H

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


class User : public QObject
{
     Q_OBJECT
public:
    User();
    void setUser(QDataStream& dsIn);
    void setUsername(QString username){this->username = username;};
    void appendPkm(Pkm* pkm){allPkmAttr.append(pkm);};
    QString getUsername(){return username;};
    Pkm* getAllPkmAttr(unsigned int num){return allPkmAttr[num];};
    void sendAllPkmAttr(QDataStream & dsOut);
    ~User();
private:
    QList<Pkm*> allPkmAttr;
    QString username;

};

#endif // USER_H
