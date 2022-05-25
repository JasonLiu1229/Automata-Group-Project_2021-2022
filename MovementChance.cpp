//
// Created by liuja on 25/05/2022.
//

#include "MovementChance.h"

MovementChance::MovementChance() {}

MovementChance::~MovementChance() {

}

MovementChance::MovementChance(MovementState *action) : action(action) {}

MovementState *MovementChance::getAction() const {
    return action;
}

void MovementChance::setAction(MovementState *newAction) {
    MovementChance::action = newAction;
}

const vector<MovementState *> &MovementChance::getAllMovements() const {
    return allMovements;
}

void MovementChance::setAllMovements(const vector<MovementState *> &newAllMovements) {
    MovementChance::allMovements = newAllMovements;
}

void MovementChance::addState(MovementState *state) {
    allMovements.push_back(state);
}
