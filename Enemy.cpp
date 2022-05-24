#include "Enemy.h"

#include <iostream>
#include <fstream>

Enemy::Enemy() {}

Enemy::Enemy(const string &name) : Player(name) {}

void Enemy::setSpeed(int speed) {
    Enemy::speed = speed;
}

int Enemy::getSpeed() const {
    return speed;
}

void Enemy::train(const string &fileName) {
    fstream file;

    int up, down, left, right;
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
