
#ifndef AUTOMATA_GROUP_PROJECT_2021_2022_PLAYER_H
#define AUTOMATA_GROUP_PROJECT_2021_2022_PLAYER_H
#include "Path.h"

class Player : public Path {
    string name;
public:
    explicit Player(string name);

    Player();

    virtual ~Player();
};


#endif //AUTOMATA_GROUP_PROJECT_2021_2022_PLAYER_H
