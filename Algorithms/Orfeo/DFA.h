#ifndef AUTOMATA_DFA_H
#define AUTOMATA_DFA_H

#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;

class Node;
class transition;
class transitionNFA;
class DFA
{
private:
    // Common components
    set<char> alphabet;
    set<Node*> nodes;
    set<Node*> finalNodes;
    set<Node*> beginNodes;
    set<transition*> transitions;
    // TFA components
    map<set<string> , bool> table;
    set<set<Node*>> markedPairs;
public:
    DFA(string filename);
    DFA(DFA &dfa1 , DFA &dfa2 , bool intersect);
    DFA();

    // Getters

    set<char> getAlphabet() const;
    set<Node*> getNodes() const;
    set<Node*> getFinal() const;
    set<Node*> getBegin() const;
    set<transition*> getTransitions() const;

    // Setters

    void setAlphabet(set<char>newAlphabet);
    void setNodes(set<Node*>newNodes);
    void setFinal(set<Node*>newFinalNodes);
    void setBegin(set<Node*>newBeginNodes);
    void setTransitions(set<transition*>newTransitions);

    // PA operations

    void evaluate(set<set<Node*>>&begin , set<transitionNFA*> &tempTransitions );
    void eliminateExtra(set<transitionNFA*> &currentSet);
    void eliminateExtra(set<transition*>&trans);

    // Standard DFA operations

    Node* transit(Node* begin , char a);
    bool accepts(string A);
    void print();

    // TFA implementation

    void createTable();
    void printTable();
    void fillTable();
    set<set<Node*>> findTransition(set<Node*> &beginNodes , char c);
    DFA minimize();

    // Operator overloads

    bool operator==(DFA &dfa2);

    // Destructor

    ~DFA();
};

#endif //AUTOMATA_DFA_H