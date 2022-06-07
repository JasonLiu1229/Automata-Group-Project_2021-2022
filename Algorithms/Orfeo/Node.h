#pragma once
#include <iostream>
#include <vector>
using namespace std;
class transition;
class Node
{
private:
    string name;
    bool starting;
    bool accepting;
public:
    Node(string name, bool starting, bool accepting);
    Node(Node* refNode);
    Node();
    void setStarting(bool starting);
    bool isStarting()const;
    void setAccepting(bool accepting);
    bool isAccepting()const;
    void setName(string name);
    string getName()const;
    ~Node();
};
