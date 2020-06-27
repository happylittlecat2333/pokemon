#include "high_attack.h"

high_attack::high_attack(SKILL skill)
{
    this->skill = skill;
    this->name = POKEMONNAME[skill];
    this->kind = HIGH_ATTACK;
    level=1, experience=0;
    attack = blood = defense = speed = BASE;
    attack += 50;
}

unsigned int high_attack::Attack()  //根据概率决定是普通攻击(normal_attack)，还是释放技能
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 rand_num(seed);	 // 大随机数
    unsigned int p = rand_num() % 5;
    if(p < 4)
        return normal_attack;
    else
        return skill;
}

void high_attack::levelUp(){
    level++;
    attack += 100;
    defense += 50;
    blood += 50;
    current_blood = blood;
    speed += 50;
}
