
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

void User::setUser(QDataStream &dsIn){  //加载pokemon数据，每次append一个pokemon数据
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
    qDebug() << "send online user num:" << allPkmAttr.length();
    qDebug() << "send online pkm" << this->username;
}

void User::setUser(Pkm** allPkm, unsigned int pkmNum)   //从login中传递的数据，加载到user对象中
{
    for(unsigned int i=0;i<pkmNum;i++){
        Pkm *tmp = new Pkm;
        tmp->name = allPkm[i]->name;
        tmp->level = allPkm[i]->level;
        tmp->experience = allPkm[i]->experience;
        tmp->attack = allPkm[i]->attack;
        tmp->blood = allPkm[i]->blood;
        tmp->defense = allPkm[i]->defense;
        tmp->speed = allPkm[i]->speed;
        tmp->kind = allPkm[i]->kind;
        tmp->skill = allPkm[i]->skill;
        allPkmAttr.append(tmp);
    }
}


QString User::getPkmAttrByIndex(unsigned int index)
{
    Pkm* tmp = this->allPkmAttr[index];
    QString all;
    all = all + "name:" + tmp->name;
    all = all + "\nlevel:" + QString::number(tmp->level);
    all = all + "\nexperience:" + QString::number(tmp->experience);
    all = all + "\nblood:" + QString::number(tmp->blood);
    all = all + "\nattack:" + QString::number(tmp->attack);
    all = all + "\ndefense:" + QString::number(tmp->defense);
    all = all + "\nspeed:" + QString::number(tmp->speed);
    all = all + "\nskill:" + ATTACKKIND[tmp->skill];
    return all;
}

int User::attackOpponent(unsigned int index)
{
    Pkm* pkm = this->allPkmAttr[index];

    int attackValue = 0;

    qsrand(QTime(0,0,0,0).msecsTo((QTime::currentTime()))); //生成随机种子
    unsigned int p = qrand() % 10 + 1;  //p:1~10
    if(p <= 3){  //0.3的几率出技能
        attackValue = -1;
    }
    else if(p >= 4 && p <=10 )   //0.7的几率出普通攻击
        attackValue = pkm->attack;
    return attackValue;
}

void User::addExperience(unsigned int index, unsigned int opLevel)
{
    unsigned int add_experience = 50 * opLevel * opLevel;
    qDebug() << "add expereince " << add_experience;
    allPkmAttr[index]->experience += add_experience;
    unsigned int experienceAll_level = 100 * this->allPkmAttr[index]->level * this->allPkmAttr[index]->level; //此level下最大经验值，超过就升级了
    while(this->allPkmAttr[index]->level < MAX_LEVEL && this->allPkmAttr[index]->experience >= experienceAll_level) //循环判断等级
    {
        levelUp(index);  //level升级（+1）
        experienceAll_level = 100 * this->allPkmAttr[index]->level * this->allPkmAttr[index]->level;
    }
}

void User::levelUp(unsigned int index)
{
    Pkm* tmp = allPkmAttr[index];
    tmp->level++;
    tmp->attack += 10;
    tmp->defense += 5;
    tmp->blood += 20;
    tmp->speed += 2;
    switch (tmp->kind) {
    case HIGH_BLOOD:
        tmp->blood += 10;
        break;
    case HIGH_ATTACK:
        tmp->attack += 5;
        break;
    case HIGH_DEFENSE:
        tmp->defense += 5;
        break;
    case HIGH_SPEED:
        tmp->speed += 2;
        break;
    }
}
