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
    void setUser(QDataStream& dsIn);     //根据传来的数据载入到用户中
    void setUsername(QString username){this->username = username;};
    void appendPkm(Pkm* pkm){allPkmAttr.append(pkm);};  //得到一个精灵
    QString getUsername(){return username;};
    Pkm* getAllPkmAttr(unsigned int num){return allPkmAttr[num];};
    void sendAllPkmAttr(QDataStream & dsOut);   //更新用户的所有信息
    int getPkmNum(){return allPkmAttr.length();};
    Pkm* getPkmByIndex(unsigned int index){return allPkmAttr[index];};
    void setUser(Pkm** allPkm, unsigned int pkmNum);    //从login界面中传递的数据，加载到用户中
    void deleteAllPkm(){allPkmAttr.clear();};
    QString getPkmAttrByIndex(unsigned int index);
    int attackOpponent(unsigned int index);     //用户的一个精灵发出攻击，返回攻击伤害
    void addExperience(unsigned int index, unsigned int opLevel);   //用户的pokemon增加经验值（根据对方精灵的等级）
    void levelUp(unsigned int index);
    void popPkmByIndex(unsigned int index){allPkmAttr.removeAt(index);};    //失去一个pokemon
    QString getUserBadget();    //返回用户徽章的情况
    unsigned int win;
    unsigned int lose;
    ~User();

private:
    QList<Pkm*> allPkmAttr;
    QString username;
    unsigned int pkmNum;
};

#endif // USER_H
