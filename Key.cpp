#include "Key.h"

Key::Key() : collected(true) {}

Key::~Key() {

}

bool Key::isCollected() const {
    return collected;
}

void Key::setCollected(bool collected) {
    Key::collected = collected;
}
