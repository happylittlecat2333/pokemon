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
#include "login.h"
#include "fight.h"

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
    int getPkmNum(){return allPkmAttr.length();};
    Pkm* getPkmByIndex(unsigned int index){return allPkmAttr[index];};
    void setUser(Pkm** allPkm, unsigned int pkmNum);
    void deleteAllPkm(){allPkmAttr.clear();};
    QString getPkmAttrByIndex(unsigned int index);
    int attackOpponent(unsigned int index);
    void addExperience(unsigned int index, unsigned int opLevel);
    void levelUp(unsigned int index);
    void popPkmByIndex(unsigned int index){allPkmAttr.removeAt(index); qDebug() << "delete" << index;pkmNum=getPkmNum();};
    QString getUserBadget();
    unsigned int win;
    unsigned int lose;
    ~User();
private:
    QList<Pkm*> allPkmAttr;
    QString username;
    unsigned int pkmNum;

};

#endif // USER_H
