
#include "Player.h"

#include <utility>

Player::Player() : dead(false) {}

Player::Player(string name) : name(std::move(name)) , dead(false){}

Player::Player(Path *currentTile, const string &name) : currentTile(currentTile), name(name) , dead(false){}

Path* Player::GetCurrentTile() {
    return currentTile;
}

void Player::SetCurrentTile(Path *temp) {
    currentTile = temp;
}

Path *Player::getUp() const {
    return up;
}

bool Player::playerdead(){
    return dead;
}

void Player::playerdied() {
    dead = true;
}

void Player::setUp(Path *up) {
    Player::up = up;
}

Path *Player::getDown() const {
    return down;
}

void Player::setDown(Path *down) {
    Player::down = down;
}

Path *Player::getLeft() const {
    return left;
}

void Player::setLeft(Path *left) {
    Player::left = left;
}

Path *Player::getRight() const {
    return right;
}

void Player::setRight(Path *right) {
    Player::right = right;
}

Path *Player::getCurrentTile() const {
    return currentTile;
}

void Player::setCurrentTile(Path *currentTile) {
    Player::currentTile = currentTile;
}

Player::~Player() {}

void Player::playerRose() {
    dead = false;
}
