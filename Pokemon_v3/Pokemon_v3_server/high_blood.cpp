#include "high_blood.h"

high_blood::high_blood(SKILL skill)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 rand_num(seed);	 // 大随机数
    unsigned int p = rand_num() % 3;
    this->skill = skill;
    this->name = POKEMONNAME[skill * 3 + p] ;
    this->kind = HIGH_BLOOD;
    level=1, experience=0;
    blood = 100;
    attack = 50;
    defense = 25;
    speed = 10;

    blood += 10;    //特殊加成
}

unsigned int high_blood::Attack()   //根据概率决定是普通攻击(normal_attack)，还是释放技能
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 rand_num(seed);	 // 大随机数
    unsigned int p = rand_num() % 5;
    if(p < 4)
        return normal_attack;
    else
        return skill;
}

void high_blood::levelUp(){
    level++;
    attack += 10;
    defense += 5;
    blood += 30;
    current_blood = blood;
    speed += 2;
}
