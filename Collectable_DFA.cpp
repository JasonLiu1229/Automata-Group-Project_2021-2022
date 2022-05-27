#include "Collectable_DFA.h"
#include "miniState.h"
using namespace std;

Collectable_DFA::Collectable_DFA() {}

Collectable_DFA::Collectable_DFA(int amount) {
    if (amount > 0) {
        for (int i = 0; i < amount; ++i) {
            auto* newMiniState = new miniState();
            if (states.empty()){
                newMiniState->setNext(newMiniState);
                newMiniState->setallcollected(true);
            }
            else {
                newMiniState->setNext(states[states.size()-1]);
            }
            states.push_back(newMiniState);
        }
        currentState = states[states.size()-1];
    }
}

miniState* Collectable_DFA::getCurrentState() const {
    return currentState;
}

void Collectable_DFA::setCurrentState(miniState *currentState) {
    Collectable_DFA::currentState = currentState;
}

Collectable_DFA::~Collectable_DFA() {

}
