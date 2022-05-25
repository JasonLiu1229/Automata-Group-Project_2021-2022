//
// Created by liuja on 25/05/2022.
//

#ifndef AUTOMATA_GROUP_PROJECT_2021_2022_MOVEMENTCHANCE_H
#define AUTOMATA_GROUP_PROJECT_2021_2022_MOVEMENTCHANCE_H
#include <vector>

using namespace std;

class MovementState;

class MovementChance {
    MovementState* action;

    vector<MovementState*> allMovements;

public:
    MovementChance();

    MovementChance(MovementState *action);

    MovementState *getAction() const;

    void setAction(MovementState *newAction);

    const vector<MovementState *> &getAllMovements() const;

    void setAllMovements(const vector<MovementState *> &newAllMovements);

    void addState(MovementState* state);

    virtual ~MovementChance();
};


#endif //AUTOMATA_GROUP_PROJECT_2021_2022_MOVEMENTCHANCE_H
