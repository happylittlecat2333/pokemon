#include "high_blood.h"

high_blood::high_blood(SKILL skill)
{
    this->skill = skill;
    this->name = POKEMONNAME[skill];
    this->kind = HIGH_BLOOD;
    level=1, experience=0;
    attack = blood = defense = speed = BASE;
    blood += 50;
}

unsigned int high_blood::Attack(){ //根据概率决定是普通攻击(normal_attack)，还是释放技能
    qsrand(QTime(0,0,0,0).msecsTo((QTime::currentTime()))); //生成随机种子
    unsigned int p = qrand() % 5;
    if(p < 4)
        return normal_attack;
    else
        return skill;
}

void high_blood::levelUp(){
    level++;
    attack += 50;
    defense += 50;
    blood += 100;
    current_blood = blood;
    speed += 50;
}
