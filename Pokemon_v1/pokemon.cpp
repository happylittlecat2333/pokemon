#include "pokemon.h"

QString pokemon::getAllValue(){
    QString all;
    all = all + "name:" + name;
    all = all + "\nlevel:" + QString::number(level);
    all = all + "\nexperience:" + QString::number(experience);
    all = all + "\nattack:" + QString::number(attack);
    all = all + "\ndefense:" + QString::number(defense);
    all = all + "\nblood:" + QString::number(blood);
    all = all + "\nspeed:" + QString::number(speed);

    return all;
}

void pokemon::setValue(unsigned int base_attack, unsigned int base_blood, unsigned int base_defense, unsigned int base_speed){
    attack = base_attack;
    blood = base_blood;
    defense = base_defense;
    speed = base_speed;
}

void pokemon::experienceUp(unsigned int value){
    experience += value;
    unsigned int experienceAll_level = 100 * level * level; //此level下最大经验值，超过就升级了
    while(level < MAX_LEVEL && experience >= experienceAll_level) //循环判断等级
    {
        levelUp();  //level升级（+1）
        experienceAll_level = 100 * level * level;
    }
}

