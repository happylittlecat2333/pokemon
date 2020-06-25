#ifndef HIGH_BLOOD_H
#define HIGH_BLOOD_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include"pokemon.h"


class high_blood : public Pokemon
{
    Q_OBJECT
public:
    high_blood(SKILL skill);
    unsigned int Attack();
    void levelUp();
    ~high_blood(){};
};

#endif // HIGH_BLOOD_H
