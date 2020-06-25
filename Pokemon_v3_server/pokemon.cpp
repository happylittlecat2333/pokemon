#include "pokemon.h"

QString Pokemon::getAllValue(){
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

void Pokemon::setValue(unsigned int base_attack, unsigned int base_blood, unsigned int base_defense, unsigned int base_speed){
    attack = base_attack;
    blood = base_blood;
    defense = base_defense;
    speed = base_speed;
}

void Pokemon::experienceUp(unsigned int value){ //增加经验
    experience += value;
    unsigned int experienceAll_level = 100 * level * level; //此level下最大经验值，超过就升级了
    while(level < MAX_LEVEL && experience >= experienceAll_level) //循环判断等级
    {
        levelUp();  //level升级（+1）
        experienceAll_level = 100 * level * level;
    }
}

void Pokemon::setLevel(unsigned int set_level){ //升级到指定等级
    unsigned int addExperience = 100 * set_level * set_level - this->experience - 1;
    this->experienceUp(addExperience);
}

Pkm* Pokemon::getAttr(){    //返回pokemon信息
    Pkm* attr = new Pkm();

    attr->name=this->name;
    attr->level=this->level;
    attr->experience=this->experience;
    attr->attack=this->attack;
    attr->blood=this->blood;
    attr->defense=this->defense;
    attr->speed=this->speed;
    attr->kind=this->kind;
    attr->skill=this->skill;

    return attr;
}

