#ifndef POKEMON_H
#define POKEMON_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QTime>
#include <QString>
#include <chrono>
#include <random>

#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

#define MAX_LEVEL 15
#define BASE 100

struct Pkm  //pokemon信息
{
    QString name;
    unsigned int level;
    unsigned int experience;
    unsigned int attack;
    unsigned int blood;
    unsigned int current_blood;
    unsigned int defense;
    unsigned int speed;
    unsigned int kind;
    unsigned int skill;
};

enum SKILL  //pokemon的特殊技能
{
    fire_attack,
    water_attack,
    defense_attack,
    double_attack,
    normal_attack   //所有精灵都有
};

enum KIND   //pokemon的所有种类
{
    HIGH_ATTACK,
    HIGH_BLOOD,
    HIGH_DEFENSE,
    HIGH_SPEED
};

const QList<QString> POKEMONNAME={  //所有pokemon的名字（特殊技能；属性）
    "Charmander",   //小火龙
    "Charmeleon",   //火恐龙
    "Charizard",    //喷火龙(fire_attack; high_attack)
    "Squirtle",     //杰尼龟
    "Wartortle",    //卡咪龟
    "Blastoise",    //水箭龟(water_attack; high_blood)
    "Diglett",      //地鼠
    "Dugtrio",      //三地鼠
    "Snorlax",      //卡比兽(defense_attack; high_defense)
    "Dodrio",       //嘟嘟利
    "Duduo",        //嘟嘟
    "Pikachu",      //皮卡丘(double_attack; high_speed)
};


const QList<QString> KINDNAME={"HIGH ATTACK","HIGH BLOOD","HIGH DEFENSE","HIGH SPEED"};//类型名称

const QList<QString> ATTACKKIND={ //特殊技能名称
    "fire_attack",
    "water_attack",
    "defense_attack",
    "double_attack",
    "normal_attack"};

class Pokemon : public QObject
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
    Pokemon(){};
    virtual unsigned int Attack(){return 0;}    //每种精灵攻击方法不一样，为虚函数，需重写
    void experienceUp(unsigned int value);      //增加精灵经验值
    QString getName(){return name;}
    QString getSkill(){return ATTACKKIND[skill];}
    unsigned int getLevel(){return level;};
    unsigned int getExperience(){return experience;};
    QString getAllValue();
    virtual void levelUp(){};   //每种精灵升级的情况不一样，为虚函数，需重写

    Pkm* getAttr();
    virtual ~Pokemon() {}

signals:
public slots:

};

#endif // POKEMON_H
