//
// Created by liuja on 25/05/2022.
//

#include "MovementChance.h"
#include <random>

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

vector<MovementState *> &MovementChance::getAllMovements() {
    return allMovements;
}

void MovementChance::setAllMovements(const vector<MovementState *> &newAllMovements) {
    MovementChance::allMovements = newAllMovements;
}

void MovementChance::addState(MovementState *state) {
    allMovements.push_back(state);
}

MovementState *MovementChance::getRandomMovement() {
    int randomN = rand() % allMovements.size();
    return allMovements[randomN];
}
