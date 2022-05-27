#include "Enemy.h"
#include "MovementChance.h"
#include "MovementState.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>


Enemy::Enemy() {
    upC->setAction(new MovementState(UP));
    downC->setAction(new MovementState(DOWN));
    leftC->setAction(new MovementState(LEFT));
    rightC->setAction(new MovementState(RIGHT));
}

Enemy::Enemy(const string &name) : Player(name) {
    upC->setAction(new MovementState(UP));
    downC->setAction(new MovementState(DOWN));
    leftC->setAction(new MovementState(LEFT));
    rightC->setAction(new MovementState(RIGHT));
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

        // stupid learning
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

        // smart learning but still stupid
        for (int i = 1; i < line.size(); ++i) {
            char c = line.at(i);
            auto* state = new MovementState();
            if (c == 'w'){
                if (line.at(i -1) == 'w'){
                    state->setAction(UP);
                    upC->addState(state);
                }
                else if (line.at(i -1)  == 'a'){
                    state->setAction(LEFT);
                    upC->addState(state);
                }
                else if (line.at(i -1)  == 'd'){
                    state->setAction(RIGHT);
                    upC->addState(state);
                }
                else if (line.at(i -1)  == 's'){
                    state->setAction(DOWN);
                    upC->addState(state);
                }
            }
            else if (c == 'a'){
                if (line.at(i -1) == 'w'){
                    state->setAction(UP);
                    leftC->addState(state);
                }
                else if (line.at(i -1)  == 'a'){
                    state->setAction(LEFT);
                    leftC->addState(state);
                }
                else if (line.at(i -1)  == 'd'){
                    state->setAction(RIGHT);
                    leftC->addState(state);
                }
                else if (line.at(i -1)  == 's'){
                    state->setAction(DOWN);
                    leftC->addState(state);
                }
            }
            else if (c == 'd'){
                if (line.at(i -1) == 'w'){
                    state->setAction(UP);
                    rightC->addState(state);
                }
                else if (line.at(i -1)  == 'a'){
                    state->setAction(LEFT);
                    rightC->addState(state);
                }
                else if (line.at(i -1)  == 'd'){
                    state->setAction(RIGHT);
                    rightC->addState(state);
                }
                else if (line.at(i -1)  == 's'){
                    state->setAction(DOWN);
                    rightC->addState(state);
                }
            }
            else if (c == 's'){
                if (line.at(i -1) == 'w'){
                    state->setAction(UP);
                    downC->addState(state);
                }
                else if (line.at(i -1)  == 'a'){
                    state->setAction(LEFT);
                    downC->addState(state);
                }
                else if (line.at(i -1)  == 'd'){
                    state->setAction(RIGHT);
                    downC->addState(state);
                }
                else if (line.at(i -1)  == 's'){
                    state->setAction(DOWN);
                    downC->addState(state);
                }
            }
        }


    }

    file.close();
}

Enemy::~Enemy() {

}

movement Enemy::moveStupid() {
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

    previousMov = action;

    return action;
}

movement Enemy::moveSmart() {
    movement action = UP;
    if (previousMov == UP){
        action = upC->getRandomMovement()->getAction();
    } else if (previousMov == DOWN){
        action = downC->getRandomMovement()->getAction();
    } else if (previousMov == LEFT){
        action = leftC->getRandomMovement()->getAction();
    } else if (previousMov == RIGHT){
        action = rightC->getRandomMovement()->getAction();
    }
    previousMov = action;
    return action;
}
