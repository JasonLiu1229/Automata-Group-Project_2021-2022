
#include "Player.h"

#include <utility>

Player::Player(string name) : name(std::move(name)) {}

Player::Player() {}

Player::~Player() {

}
