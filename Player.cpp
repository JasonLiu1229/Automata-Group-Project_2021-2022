
#include "Player.h"

#include <utility>

Player::Player() {}

Player::Player(string name) : name(std::move(name)) {}

Player::Player(Path *currentTile, const string &name) : currentTile(currentTile), name(name) {}

Player::~Player() {}
