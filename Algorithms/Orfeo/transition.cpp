#include "transition.h"
#include "Node.h"
#include <iostream>
using namespace std;


transition::transition(Node* beginNode, Node* endNode, char inputA) : beginNode(beginNode) , endNode(endNode) , inputA(inputA){}

transition::transition(transition* refTran) :   beginNode( refTran->getBeginNode() ) ,
                                                endNode( refTran->getEndNode() ) ,
                                                inputA( refTran->getInput() ){}
transition::transition() : beginNode(nullptr) , endNode(nullptr) , inputA(' ') {}

Node* transition::getBeginNode(){
    return beginNode;
}
void transition::setBeginNode(Node* n){
    beginNode = n;
}
Node* transition::getEndNode(){
    return endNode;
}
void transition::setEndNode(Node* e){
    endNode = e;
}
char transition::getInput(){
    return inputA;
}
void transition::setInput(char a){
    inputA = a;
}

transition::~transition()
{
}
