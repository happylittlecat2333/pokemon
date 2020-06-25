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
    void levelUp();
    ~high_defense(){};
};

#endif
