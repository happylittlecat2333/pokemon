#ifndef HIGH_SPEED_H
#define HIGH_SPEED_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include"pokemon.h"


class high_speed : public pokemon
{
    Q_OBJECT
public:
    high_speed(SKILL skill);
    unsigned int Attack();
    void levelUp();
    ~high_speed(){};
};

#endif
