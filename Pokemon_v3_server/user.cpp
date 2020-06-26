
#include "user.h"

User::User()
{
    allPkmAttr.clear();
}


User::~User()
{
    while(!allPkmAttr.empty())
        delete allPkmAttr.takeFirst();
}


void User::setUser(QDataStream &dsIn)  //设置用户的pokemon信息，每次append一个pokemon
{
    Pkm *tmp = new Pkm;
    dsIn >> tmp->name;
    dsIn >> tmp->level;
    dsIn >> tmp->experience;
    dsIn >> tmp->attack;
    dsIn >> tmp->blood;
    dsIn >> tmp->defense;
    dsIn >> tmp->speed;
    dsIn >> tmp->kind;
    dsIn >> tmp->skill;
    allPkmAttr.append(tmp);
}


void User::sendAllPkmAttr(QDataStream &dsOut)   //???好像没有用到这个函数
{
    dsOut << this->username;
    dsOut << this->win;
    dsOut << this->lose;
    dsOut << allPkmAttr.length();
    for(int i=0; i<allPkmAttr.length(); i++){
        dsOut << allPkmAttr[i]->name;
        dsOut << allPkmAttr[i]->level;
        dsOut << allPkmAttr[i]->experience;
        dsOut << allPkmAttr[i]->attack;
        dsOut << allPkmAttr[i]->blood;
        dsOut << allPkmAttr[i]->defense;
        dsOut << allPkmAttr[i]->speed;
        dsOut << allPkmAttr[i]->kind;
        dsOut << allPkmAttr[i]->skill;
    }
    qDebug() << "send online pkm" << this->username;
}
