
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


void User::sendAllPkmAttr(QDataStream &dsOut)   //更新用户的所有信息
{
    dsOut << this->username;
    dsOut << this->win;
    dsOut << this->lose;
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
}


void User::setUser(Pkm** allPkm, unsigned int pkmNum)   //从login中传递的数据，加载到用户中
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


QString User::getUserBadget()   //返回用户宠物个数徽章、高级精灵个数徽章
{
    QString s;
    unsigned int high_rank_num = 0;
    for(QList<Pkm*>::iterator i=allPkmAttr.begin(); i!=allPkmAttr.end(); ++i){
        if((*i)->level == 15) high_rank_num++;
    }
    pkmNum = getPkmNum();
    s = QString::number(pkmNum)+" pokemon\n";
    s += "pokemon_badget: ";
    if(pkmNum <= 3) s += "Copper";
    else if(pkmNum <= 5) s += "Silver";
    else s += "Gold";

    s += "\nhight_rank_badegt: ";
    if(high_rank_num <= 3) s += "Copper";
    else if(high_rank_num <= 5) s += "Silver";
    else s += "Gold";
    return s;
}


QString User::getPkmAttrByIndex(unsigned int index) //返回pokemon信息
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


int User::attackOpponent(unsigned int index)    //用户的一个精灵发出攻击，返回攻击伤害
{
    int attackValue = 0;

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();    //随机种子
    std::mt19937 rand_num(seed);
    unsigned int p = rand_num() % 10 + 1;  //p的范围1~10
    if(p <= 3)                  //0.3的几率出技能
        attackValue = -1;
    else if(p >= 4 && p <=10)   //0.7的几率出普通攻击
        attackValue = this->allPkmAttr[index]->attack;

    return attackValue;
}


void User::addExperience(unsigned int index, unsigned int opLevel)  //用户的一个pokemon增加经验值（根据对方精灵的等级）
{
    unsigned int add_experience = 50 * opLevel * opLevel;
    unsigned int current_level = this->allPkmAttr[index]->level;
    allPkmAttr[index]->experience += add_experience;

    unsigned int experienceAll_level = 100 * current_level * current_level; //此level下最大经验值，超过就升级了
    while(current_level < MAX_LEVEL && this->allPkmAttr[index]->experience >= experienceAll_level) //循环判断等级
    {
        levelUp(index);  //level升级（+1）
        current_level = this->allPkmAttr[index]->level;
        experienceAll_level = 100 * current_level * current_level;
    }
}


void User::levelUp(unsigned int index)  //用户的pokemon升级
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
