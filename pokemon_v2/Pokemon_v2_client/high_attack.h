#ifndef HIGH_ATTACK_H
#define HIGH_ATTACK_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include"pokemon.h"


class high_attack : public Pokemon
{
    Q_OBJECT
public:
    high_attack(SKILL skill);
    unsigned int Attack();
    void levelUp();
    ~high_attack(){};
};

#endif // HIGH_ATTACK_H
