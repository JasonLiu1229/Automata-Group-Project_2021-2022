
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

    bool dead;

    // amount of keys
    int amountKeys = 0;
public:
    explicit Player(string name);

    Player(Path *currentTile, const string &name);

    Player();

    Path* GetCurrentTile();

    void SetCurrentTile(Path* temp);

    Path *getUp() const;

    void setUp(Path *up);

    Path *getDown() const;

    void setDown(Path *down);

    Path *getLeft() const;

    void setLeft(Path *left);

    Path *getRight() const;

    void setRight(Path *right);

    Path *getCurrentTile() const;

    void setCurrentTile(Path *currentTile);

    bool playerdead();

    bool playerRose();

    void playerdied();

    virtual ~Player();
};


#endif //AUTOMATA_GROUP_PROJECT_2021_2022_PLAYER_H
