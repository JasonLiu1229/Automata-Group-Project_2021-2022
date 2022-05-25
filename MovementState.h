//
// Created by liuja on 25/05/2022.
//

#ifndef AUTOMATA_GROUP_PROJECT_2021_2022_MOVEMENTSTATE_H
#define AUTOMATA_GROUP_PROJECT_2021_2022_MOVEMENTSTATE_H
#include "Standard_Values.h"

class MovementState {
public:
    MovementState();

    virtual ~MovementState();

    movement getAction() const;

    void setAction(movement action);

private:
    movement action;

};


#endif //AUTOMATA_GROUP_PROJECT_2021_2022_MOVEMENTSTATE_H
