#ifndef HIGH_DEFENSE_H
#define HIGH_DEFENSE_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include"pokemon.h"


class high_defense : public Pokemon
{
    Q_OBJECT
public:
    high_defense(SKILL skill);
    unsigned int Attack();
    void levelUp();     //重写不同种类的精灵的升级方式
    ~high_defense(){};
};

#endif
