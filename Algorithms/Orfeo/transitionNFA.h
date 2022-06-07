#include <iostream>
#include <set>
using namespace std;
class Node;
class transitionNFA
{
private:
    set<Node*> beginNodes;
    set<Node*> endNodes;
    char inputA;
public:
    transitionNFA(set<Node*> beginNodes, set<Node*> endNodes, char inputA);
    transitionNFA(transitionNFA* refTran);
    transitionNFA();
    set<Node*> getBeginNodes();
    void setBeginNodes(set<Node*> n);
    set<Node*> getEndNodes();
    void setEndNodes(set<Node*> e);
    char getInput();
    void setInput(char a);
    ~transitionNFA();
};