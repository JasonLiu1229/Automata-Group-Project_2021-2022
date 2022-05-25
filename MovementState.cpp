//
// Created by liuja on 25/05/2022.
//

#include "MovementState.h"

MovementState::MovementState() {}

MovementState::~MovementState() {

}

movement MovementState::getAction() const {
    return action;
}

void MovementState::setAction(movement action) {
    MovementState::action = action;
}

MovementState::MovementState(movement action) : action(action) {}
