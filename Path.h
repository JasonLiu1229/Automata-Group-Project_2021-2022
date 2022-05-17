
#ifndef AUTOMATA_GROUP_PROJECT_2021_2022_PATH_H
#define AUTOMATA_GROUP_PROJECT_2021_2022_PATH_H
#include <iostream>

#include "Standard_Values.h"

using namespace std;

class Player;

class Path {
    // direction it can move to
    Path* left;
    Path* up;
    Path* down;
    Path* right;

    // tile settings
    tileSettings settings;

    // state is starting or final
    bool starting;
    bool accepting;

    // key
    bool key;

public:
    Path();

    bool isAccepting() const;

    void setAccepting(bool accepting);

    Path *getLeft() const;

    void setLeft(Path *left);

    Path *getUp() const;

    void setUp(Path *up);

    Path *getDown() const;

    void setDown(Path *down);

    Path *getRight() const;

    void setRight(Path *right);

    bool isStarting() const;

    void setStarting(bool starting);

    tileSettings getSettings() const;

    void setSettings(tileSettings new_settings);

    bool isKey() const;

    void setKey(bool key);

    virtual ~Path();
};


#endif //AUTOMATA_GROUP_PROJECT_2021_2022_PATH_H
