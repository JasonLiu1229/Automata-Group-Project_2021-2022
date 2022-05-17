//
// Created by liuja on 17/05/2022.
//

#include "miniState.h"

miniState::miniState() {}

miniState *miniState::getNext() const {
    return next;
}

void miniState::setNext(miniState *next) {
    miniState::next = next;
}

miniState::~miniState() {

}
