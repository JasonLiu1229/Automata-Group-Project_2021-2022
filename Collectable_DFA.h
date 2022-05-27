//
// Created by jason on 10/05/2022.
//

#ifndef AUTOMATA_GROUP_PROJECT_2021_2022_COLLECTABLE_DFA_H
#define AUTOMATA_GROUP_PROJECT_2021_2022_COLLECTABLE_DFA_H
#include <vector>

using namespace std;

class miniState;
class Collectable_DFA {
    vector<miniState*> states;
    miniState* currentState;
public:
    Collectable_DFA();

    explicit Collectable_DFA(int amount);

    miniState* getCurrentState() const;

    void setCurrentState(miniState *currentState);

    virtual ~Collectable_DFA();
};


#endif //AUTOMATA_GROUP_PROJECT_2021_2022_COLLECTABLE_DFA_H
