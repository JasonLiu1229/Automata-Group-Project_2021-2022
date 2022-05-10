#include "Enemy.h"

Enemy::Enemy() {}

Enemy::Enemy(const string &name) : Player(name) {}

void Enemy::setSpeed(int speed) {
    Enemy::speed = speed;
}

int Enemy::getSpeed() const {
    return speed;
}

Enemy::~Enemy() {

}
