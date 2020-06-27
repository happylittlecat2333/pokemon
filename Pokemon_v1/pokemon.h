#ifndef POKEMON_H
#define POKEMON_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QTime>
#include <QString>

#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

#define MAX_LEVEL 15
#define BASE 100

enum SKILL
{
    fire_attack,
//    light_attack,
    water_attack,
    defense_attack,
    double_attack,
    normal_attack   //所有精灵都有
};

enum KIND
{
    HIGH_ATTACK,
    HIGH_BLOOD,
    HIGH_DEFENSE,
    HIGH_SPEED
};

const QList<QString> POKEMONNAME={
    "Charizard", //喷火龙(fire_attack; high_attack)
//    "Pikachu",   //皮卡丘(light_attack)
    "Blastoise", //水箭龟(water_attack; high_blood)
    "Snorlax",   //卡比兽(defense_attack; high_defense)
    "Duduo",     //嘟嘟(double_attack; high_speed)
};
const QList<QString> KINDNAME={"HIGH ATTACK","HIGH BLOOD","HIGH DEFENSE","HIGH SPEED"};//类型名称
const QList<QString> ATTACKKIND={
    "fire_attack",
//    "light_attack",
    "water_attack",
    "defense_attack",
    "double_attack",
    "normal_attack"};

class pokemon : public QObject
{
    Q_OBJECT

protected:
    QString name;
    unsigned int level;
    unsigned int experience;
    unsigned int attack;
    unsigned int blood;
    unsigned int current_blood;
    unsigned int defense;
    unsigned int speed;
    unsigned int kind;
    SKILL skill;
    void setValue(unsigned int base_attack, unsigned int base_blood, unsigned int base_defense, unsigned int base_speed);

public:
    pokemon(){};
    virtual unsigned int Attack(){return 0;}    //每种精灵攻击方法不一样，为虚函数，需重写
    void experienceUp(unsigned int value);
    QString getName(){return name;}
    QString getSkill(){return ATTACKKIND[skill];}
    unsigned int getLevel(){return level;};
    unsigned int getExperience(){return experience;};
    QString getAllValue();
    virtual void levelUp(){};   //每种精灵升级的情况不一样，为虚函数，需重写
    virtual ~pokemon() {}

signals:
public slots:

};

#endif // POKEMON_H
