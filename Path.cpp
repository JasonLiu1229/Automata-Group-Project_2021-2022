#include "Path.h"

Path::Path() : up(nullptr), down(nullptr), left(nullptr), right(nullptr), starting(false), accepting(false), settings(path) {}

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

bool Path::isStarting() const {
    return starting;
}

void Path::setStarting(bool start) {
    Path::starting = start;
}

bool Path::isAccepting() const {
    return accepting;
}

void Path::setAccepting(bool accepting) {
    Path::accepting = accepting;
}

tileSettings Path::getSettings() const {
    return settings;
}

void Path::setSettings(tileSettings new_settings) {
    Path::settings = new_settings;
}

Path::~Path() {}
