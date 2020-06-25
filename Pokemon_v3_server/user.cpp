
#include "user.h"

User::User()
{
    allPkmAttr.clear();
}

User::~User()
{
    qDebug() << "deleting User";
    while(!allPkmAttr.empty()){
        delete allPkmAttr.takeFirst();
    }
}

void User::setUser(QDataStream &dsIn){  //设置用户的pokemon信息，每次append一个pokemon
//    while(!dsIn.atEnd()){
        Pkm *tmp = new Pkm;
        dsIn >> tmp->name;
//        qDebug() << tmp->name;
        dsIn >> tmp->level;
//        qDebug() << tmp->level;
        dsIn >> tmp->experience;
        dsIn >> tmp->attack;
//        qDebug() << tmp->attack;
        dsIn >> tmp->blood;
        dsIn >> tmp->defense;
        dsIn >> tmp->speed;
        dsIn >> tmp->kind;
        dsIn >> tmp->skill;
//        qDebug() << "setUser";
        allPkmAttr.append(tmp);
//    }
}

void User::sendAllPkmAttr(QDataStream &dsOut)
{
    dsOut << this->username;
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
