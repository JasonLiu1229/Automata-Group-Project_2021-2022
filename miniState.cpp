//
// Created by liuja on 17/05/2022.
//

#include "miniState.h"

miniState::miniState() {
    allCollected = false;
}

void miniState::setallcollected(bool done) {
    allCollected = done;
}

bool miniState::getkeystate() {
    return allCollected;
}

void miniState::setNext(miniState *next) {
    miniState::next = next;
}

miniState* miniState::getNext() const {
    return next;
}

miniState::~miniState() {

}
