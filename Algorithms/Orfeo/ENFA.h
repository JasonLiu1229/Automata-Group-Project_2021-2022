#ifndef AUTOMATA_ENFA_H
#define AUTOMATA_ENFA_H

#include "DFA.h"

using namespace std;

class ENFA
{
private:
    set<char> alphabet;
    set<Node*> nodes;
    set<Node*> finalNodes;
    set<Node*> beginNodes;
    set<transition*> transitions;
    set<transition*> epsTransitions;
    char eps;
public:
    ENFA(string filename);
    ENFA(ENFA* &ref);
    ENFA();
    // Getters
    set<char> getAlphabet() const;
    set<Node*> getNodes() const;
    set<Node*> getFinal() const;
    set<Node*> getBegin() const;
    set<transition*> getTransitions() const;
    set<transition*> getEpsTransitions() const;
    char getEps() const;
    // Setters
    void setAlphabet(set<char>newAlphabet);
    void setNodes(set<Node*>newNodes);
    void setFinal(set<Node*>newFinalNodes);
    void setBegin(set<Node*>newBeginNodes);
    void setTransitions(set<transition*>newTransitions);
    void setEpsTransitions(set<transition*> newEpsTransitions);
    void setEps(char newEps);
    // Help functions
    void eliminateExtra(set<transitionNFA*> &currentSet);
    void evaluate(set<set<Node*>> &newNodes , set<transitionNFA*> &tempTransitions);
    set<Node*> transit(set<Node*> begin , char a);
    set<Node*> eclose(set<Node*>);
    bool accepts(string A);
    DFA toDFA();
    void print();
    void printStats();
    // Destructor
    ~ENFA();
};

#endif //AUTOMATA_ENFA_H
