#include "Enemy.h"
#include "MovementChance.h"
#include "MovementState.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>


Enemy::Enemy(): upC(new MovementChance()), downC(new MovementChance()), leftC(new MovementChance()), rightC(new MovementChance()), previousMov(IDLE), speed(1), follow(
        false){
    MovementState* state;
    state = new MovementState(UP);
    upC->setAction(state);
    state = new MovementState(DOWN);
    downC->setAction(state);
    state = new MovementState(LEFT);
    leftC->setAction(state);
    state = new MovementState(RIGHT);
    rightC->setAction(state);
}

Enemy::Enemy(const string &name) : Player(name),upC(new MovementChance()), downC(new MovementChance()), leftC(new MovementChance()), rightC(new MovementChance()), previousMov(IDLE), speed(1), follow(
        false) {
    MovementState* state;
    state = new MovementState(UP);
    upC->setAction(state);
    state = new MovementState(DOWN);
    downC->setAction(state);
    state = new MovementState(LEFT);
    leftC->setAction(state);
    state = new MovementState(RIGHT);
    rightC->setAction(state);
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

void Enemy::moveAction(movement &action) {
    auto rng = default_random_engine {};
    if (previousMov == UP){
        shuffle(begin(upC->getAllMovements()), end(upC->getAllMovements()), rng);
        action = upC->getRandomMovement()->getAction();
    } else if (previousMov == DOWN){
        shuffle(begin(downC->getAllMovements()), end(downC->getAllMovements()), rng);
        action = downC->getRandomMovement()->getAction();
    } else if (previousMov == LEFT){
        shuffle(begin(leftC->getAllMovements()), end(leftC->getAllMovements()), rng);
        action = leftC->getRandomMovement()->getAction();
    } else if (previousMov == RIGHT){
        shuffle(begin(rightC->getAllMovements()), end(rightC->getAllMovements()), rng);
        action = rightC->getRandomMovement()->getAction();
    }
}

movement Enemy::moveSmart() {
    movement action = UP;
    moveAction(action);
    previousMov = action;
    return action;
}

movement Enemy::moveSmartV2() {
    movement action;
    if (previousMov == IDLE){
        // check which path is free and choose by random with chance == 1 / [amount of valid moves]
    } else {
        moveAction(action);
        // check if this move is to a valid tile, if not redo everything until valid
        if (action == UP){

        } else if (action == DOWN){

        } else if (action == LEFT){

        } else if (action == RIGHT){

        }
    }
    previousMov = action;
    return action;
}
