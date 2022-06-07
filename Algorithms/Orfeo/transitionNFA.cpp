#include "transitionNFA.h"
#include <iostream>
using namespace std;


transitionNFA::transitionNFA(set<Node*> beginNodes, set<Node*> endNodes, char inputA) :
                beginNodes(beginNodes) , endNodes(endNodes) , inputA(inputA) {}

transitionNFA::transitionNFA(transitionNFA* refTran) : 
                beginNodes( refTran->getBeginNodes() ),
                endNodes( refTran->getEndNodes() ),
                inputA( refTran->getInput() ) {}

transitionNFA::transitionNFA() : beginNodes({}) , endNodes({}) , inputA(' ') {}

set<Node*> transitionNFA::getBeginNodes(){
    return beginNodes;
}
void transitionNFA::setBeginNodes(set<Node*> n){
    beginNodes = n;
}
set<Node*> transitionNFA::getEndNodes(){
    return endNodes;
}
void transitionNFA::setEndNodes(set<Node*> e){
    endNodes = e;
}
char transitionNFA::getInput(){
    return inputA;
}
void transitionNFA::setInput(char a){
    inputA = a;
    }

transitionNFA::~transitionNFA()
{
}
