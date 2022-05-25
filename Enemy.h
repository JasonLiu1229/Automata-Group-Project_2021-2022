
#ifndef AUTOMATA_GROUP_PROJECT_2021_2022_ENEMY_H
#define AUTOMATA_GROUP_PROJECT_2021_2022_ENEMY_H
#include "Player.h"
#include "Standard_Values.h"

#include <map>
#include <vector>

using namespace std;

class MovementChance;

class Enemy : public Player{
    int speed;

    bool follow;

    map<movement, double> chances;

    MovementChance* upC;
    MovementChance* downC;
    MovementChance* leftC;
    MovementChance* rightC;

public:
    Enemy();

    Enemy(const string &name);

    virtual ~Enemy();

    int getSpeed() const;

    void setSpeed(int speed);

    void train(const string &fileName);

    movement move();
};


#endif //AUTOMATA_GROUP_PROJECT_2021_2022_ENEMY_H
