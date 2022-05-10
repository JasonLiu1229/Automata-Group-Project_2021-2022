
#ifndef AUTOMATA_GROUP_PROJECT_2021_2022_PATH_H
#define AUTOMATA_GROUP_PROJECT_2021_2022_PATH_H
#include <iostream>

using namespace std;

class Path {
    // direction it can move to
    Path* left;
    Path* up;
    Path* down;
    Path* right;

    // state is starting or final
    bool start;
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

    virtual ~Path();
};


#endif //AUTOMATA_GROUP_PROJECT_2021_2022_PATH_H
