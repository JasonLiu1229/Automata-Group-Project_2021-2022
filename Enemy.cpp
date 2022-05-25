#include "Enemy.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>

Enemy::Enemy() {
}

Enemy::Enemy(const string &name) : Player(name) {
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

        double ww, wa, ws, wd, aw, aa, as, ad, sw, sa, ss, sd, dw, da, ds, dd;
        for (int i = 1; i < line.size(); ++i) {
            char c = line.at(i);
            if (c == 'w'){
                if (line.at(i -1) == 'w'){
                    ww++;
                }
                else if (line.at(i -1)  == 'a'){
                    wa++;
                }
                else if (line.at(i -1)  == 'd'){
                    wd++;
                }
                else if (line.at(i -1)  == 's'){
                    ws++;
                }
            }
            else if (c == 'a'){
                if (line.at(i -1) == 'w'){
                    aw++;
                }
                else if (line.at(i -1)  == 'a'){
                    aa++;
                }
                else if (line.at(i -1)  == 'd'){
                    ad++;
                }
                else if (line.at(i -1)  == 's'){
                    as++;
                }
            }
            else if (c == 'd'){
                if (line.at(i -1) == 'w'){
                    dw++;
                }
                else if (line.at(i -1)  == 'a'){
                    da++;
                }
                else if (line.at(i -1)  == 'd'){
                    dd++;
                }
                else if (line.at(i -1)  == 's'){
                    ds++;
                }
            }
            else if (c == 's'){
                if (line.at(i -1) == 'w'){
                    sw++;
                }
                else if (line.at(i -1)  == 'a'){
                    sa++;
                }
                else if (line.at(i -1)  == 'd'){
                    sd++;
                }
                else if (line.at(i -1)  == 's'){
                    ss++;
                }
            }
        }


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
