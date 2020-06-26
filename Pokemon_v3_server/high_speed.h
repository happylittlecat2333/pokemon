#ifndef HIGH_SPEED_H
#define HIGH_SPEED_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include"pokemon.h"


class high_speed : public Pokemon
{
    Q_OBJECT
public:
    high_speed(SKILL skill);
    unsigned int Attack();
    void levelUp();     //重写不同种类的精灵的升级方式
    ~high_speed(){};
};

#endif
