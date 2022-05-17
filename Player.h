
#ifndef AUTOMATA_GROUP_PROJECT_2021_2022_PLAYER_H
#define AUTOMATA_GROUP_PROJECT_2021_2022_PLAYER_H
#include <string>

using namespace std;

class Path;

class Player {
    Path* up;
    Path* down;
    Path* left;
    Path* right;

    Path* currentTile;

    string name;

    // amount of keys
    int amountKeys = 0;
public:
    explicit Player(string name);

    Player(Path *currentTile, const string &name);

    Player();

    virtual ~Player();
};


#endif //AUTOMATA_GROUP_PROJECT_2021_2022_PLAYER_H
