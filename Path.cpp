#include "Path.h"

Path::Path() : up(nullptr), down(nullptr), left(nullptr), right(nullptr), start(false), accepting(false) {}

Path *Path::getLeft() const {
    return left;
}

void Path::setLeft(Path *left) {
    Path::left = left;
}

Path *Path::getUp() const {
    return up;
}

void Path::setUp(Path *up) {
    Path::up = up;
}

Path *Path::getDown() const {
    return down;
}

void Path::setDown(Path *down) {
    Path::down = down;
}

Path *Path::getRight() const {
    return right;
}

void Path::setRight(Path *right) {
    Path::right = right;
}

bool Path::isStart() const {
    return start;
}

void Path::setStart(bool start) {
    Path::start = start;
}

bool Path::isAccepting() const {
    return accepting;
}

void Path::setAccepting(bool accepting) {
    Path::accepting = accepting;
}

Path::~Path() {}
