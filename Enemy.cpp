#include "Enemy.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>

Enemy::Enemy() {
    chances[UP] = 1/4;
    chances[DOWN] = 1/4;
    chances[LEFT] = 1/4;
    chances[RIGHT] = 1/4;
}

Enemy::Enemy(const string &name) : Player(name) {
    chances[UP] = 1/4;
    chances[DOWN] = 1/4;
    chances[LEFT] = 1/4;
    chances[RIGHT] = 1/4;
}

void Enemy::setSpeed(int speed) {
    Enemy::speed = speed;
}

int Enemy::getSpeed() const {
    return speed;
}

void Enemy::train(const string &fileName) {
    fstream file;

    double up, down, left, right;
    up = down = left = right = 0;

    file.open(fileName.c_str(), ios::in);

    string line;

    if (file.is_open())
    {
        getline(file, line);
        for (const auto &c : line) {
            if (c == 'w'){
                up++;
            }
            else if (c == 'a'){
                left++;
            }
            else if (c == 'd'){
                right++;
            }
            else if (c == 's'){
                down++;
            }
        }
        chances[UP] = (up/line.size() + chances[UP])/2;
        chances[DOWN] = (down/line.size() + chances[DOWN])/2;
        chances[LEFT] = (left/line.size() + chances[LEFT])/2;
        chances[RIGHT] = (right/line.size() + chances[RIGHT])/2;
    }

    file.close();
}

Enemy::~Enemy() {

}

movement Enemy::move() {
    movement action;

    vector<movement> movementChances;

    int amountOfMov = 100;

    // add up
    for (int i = 0; i < amountOfMov * chances[UP]; ++i) {
        movementChances.push_back(UP);
    }

    // add down
    for (int i = 0; i < amountOfMov * chances[DOWN]; ++i) {
        movementChances.push_back(DOWN);
    }

    // add left
    for (int i = 0; i < amountOfMov * chances[LEFT]; ++i) {
        movementChances.push_back(LEFT);
    }

    // add right
    for (int i = 0; i < amountOfMov * chances[RIGHT]; ++i) {
        movementChances.push_back(RIGHT);
    }

    auto rng = default_random_engine {};
    shuffle(begin(movementChances), end(movementChances), rng);

    int random = rand() % movementChances.size();

    action = movementChances[random];

    return action;
}
