
#ifndef AUTOMATA_GROUP_PROJECT_2021_2022_PATH_H
#define AUTOMATA_GROUP_PROJECT_2021_2022_PATH_H
#include <iostream>

#include "Standard_Values.h"

using namespace std;

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

    bool isStart() const;

    void setStart(bool start);

    tileSettings getSettings() const;

    void setSettings(tileSettings new_settings);

    virtual ~Path();
};


#endif //AUTOMATA_GROUP_PROJECT_2021_2022_PATH_H
