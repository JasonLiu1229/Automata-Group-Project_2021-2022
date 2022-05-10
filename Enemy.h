
#ifndef AUTOMATA_GROUP_PROJECT_2021_2022_ENEMY_H
#define AUTOMATA_GROUP_PROJECT_2021_2022_ENEMY_H
#include "Player.h"

class Enemy : public Player{
    int speed;
public:
    Enemy();

    Enemy(const string &name);

    virtual ~Enemy();

    int getSpeed() const;

    void setSpeed(int speed);
};


#endif //AUTOMATA_GROUP_PROJECT_2021_2022_ENEMY_H
