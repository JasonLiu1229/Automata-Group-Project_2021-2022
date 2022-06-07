#include "ENFA.h"
#include "Node.h"
#include "transition.h"
#include "transitionNFA.h"
#include <fstream>
#include <iomanip>
#include "json.hpp"
using namespace std;

using json = nlohmann::json;

ENFA::ENFA(string filename)
{
    // Read from file
    ifstream input(filename);
    json j;
    input >> j;

    for (json::iterator it = j.begin(); it != j.end(); ++it) {
        // Designate alphabet
        if(it.key() == "alphabet"){
          vector<string> a = it.value();
          for(string s : a){
            alphabet.insert(s[0]);
            }
        }
        // Get the character for epsilon
        else if(it.key() == "eps"){
            auto a = it.value().begin();
            string eps = a[0];
            ENFA::eps = eps[0];
        }
    }
    
    // Create the nodes
    auto states = j["states"];
    for(auto state : states){
        Node* newState = new Node(state["name"],state["starting"],state["accepting"]);
        nodes.insert(newState);
    }
    // Designate begin and final nodes
    for(Node* n : nodes){
        if(n->isAccepting()){
            finalNodes.insert(n);
        }
        if(n->isStarting()){
            beginNodes.insert(n);
        }
    }
    // Add transitions
    // Create transitions array
    auto ts = j["transitions"];
    Node* beginState;
    Node* endState;
    for(auto t : ts){
        string beginNodeName = t["from"];
        string endNodeName = t["to"];
        string input = t["input"];
        char inputA = input[0];
        for(Node* n : nodes){
            if(n->getName()==beginNodeName){
                beginState = n;
            }
            if(n->getName()==endNodeName){
                endState = n;
            }
        }
        transition* newTransition = new transition(beginState,endState,inputA);
        if(inputA == ENFA::eps){
            epsTransitions.insert(newTransition);
        }
        transitions.insert(newTransition);
    }
}

ENFA::ENFA() : alphabet({}) , eps('*') , nodes({}) , beginNodes({}) , finalNodes({}) , transitions({}) , epsTransitions({}){}

ENFA::ENFA(ENFA* &ref) : alphabet(ref->getAlphabet()) , eps(ref->getEps()) ,
                 nodes(ref->getNodes()) , beginNodes(ref->getBegin()) , finalNodes(ref->getFinal()) , 
                 transitions(ref->getTransitions()) , epsTransitions(ref->getEpsTransitions()) {}

set<char> ENFA::getAlphabet() const{
    return ENFA::alphabet;
}
set<Node*> ENFA::getNodes() const{
    return ENFA::nodes;
}
set<Node*> ENFA::getFinal() const{
    return ENFA::finalNodes;
}
set<Node*> ENFA::getBegin() const{
    return ENFA::beginNodes;
}
set<transition*> ENFA::getTransitions() const{
    return ENFA::transitions;
}

set<transition*> ENFA::getEpsTransitions() const{
    return ENFA::epsTransitions;
}

char ENFA::getEps() const{
    return ENFA::eps;
}

void ENFA::setAlphabet(set<char>newAlphabet){
    ENFA::alphabet = newAlphabet;
}
void ENFA::setNodes(set<Node*>newNodes){
    ENFA::nodes = newNodes;
}
void ENFA::setFinal(set<Node*>newFinalNodes){
    ENFA::finalNodes = newFinalNodes;
}
void ENFA::setBegin(set<Node*>newBeginNodes){
    ENFA::beginNodes = newBeginNodes;
}
void ENFA::setTransitions(set<transition*>newTransitions){
    ENFA::transitions = newTransitions;
}

void ENFA::setEpsTransitions(set<transition*> newEpsTransitions){
    ENFA::epsTransitions = newEpsTransitions;
}

void ENFA::setEps(char newEps){
    ENFA::eps = newEps;
}

set<Node*> ENFA::transit(set<Node*> begin , char a){
    set<Node*> c;
    for(transition* t : transitions){
        for(Node* n : begin){
            if(t->getBeginNode() == n && t->getInput() == a){
                c.insert(t->getEndNode());
            }
        } 
    }
    return c;
}

set<Node*> ENFA::eclose(set<Node*> begin){
    set<Node*> end = begin;
    bool eval = true;
    while(eval){
        int oldSize = end.size();
        for(Node* n : end){
            for(transition* t : epsTransitions){
                if(t->getBeginNode() == n){
                    end.emplace(t->getEndNode());
                }
            }
        }
        eval = oldSize != end.size();
    }   
    return end;
}

void ENFA::eliminateExtra(set<transitionNFA*> &currentSet){
    for (auto it1 = currentSet.begin(); it1 != currentSet.end(); it1++){
        for (auto it2 = currentSet.begin(); it2 != currentSet.end(); it2++){
            if(it1 == it2){
                continue;
            }
            // Check for duplicate
            auto t1 = *it1;
            auto t2 = *it2;
            set<Node*> b1 = t1->getBeginNodes();
            set<Node*> e1 = t1->getEndNodes();
            set<Node*> b2 = t2->getBeginNodes();
            set<Node*> e2 = t2->getEndNodes();
            char c1 = t1->getInput();
            char c2 = t2->getInput();
            if( b1 == b2 && e1 == e2 && c1 == c2 ){
                delete t2;
                it2 = currentSet.erase(it2);
            }
        }
    }
}

void ENFA::evaluate(set<set<Node*>> &newNodes , set<transitionNFA*> &tempTransitions){
    bool evaluate = true;
    transitionNFA* newTransition;
    while(evaluate){
        // Remember old size
        int oldSize = newNodes.size();
        for(set<Node*>tempNodes : newNodes){
            //printNode(tempNodes);
            set<Node*> oldTemp = tempNodes;
            for(char c : alphabet){
                // Transit for character c and eclose
                tempNodes = transit(tempNodes,c);
                tempNodes = eclose(tempNodes);
                // Add newly acquired set to newNodes
                newNodes.insert(tempNodes);
                if( tempNodes.size() > 0 ){
                    // Add used transitions
                    newTransition = new transitionNFA();
                    newTransition->setBeginNodes(oldTemp);
                    // Add end nodes to transition
                    newTransition->setEndNodes(tempNodes);
                    newTransition->setInput(c);
                    // Add transition to container
                    tempTransitions.insert(newTransition);
                }  
                // Reset tempNodes
                tempNodes = oldTemp;
            }
        }
        evaluate = oldSize != newNodes.size();
    }
}

bool ENFA::accepts(string A){
    // Split string into chars
    vector<char> v(A.begin(),A.end());
    set<Node*> currentNodes = beginNodes;
    set<Node*> temp;
    for(char inputA : v){
        // Transit with character
        temp = currentNodes;
        // Get all epsilon transitions
        if(currentNodes.empty()){
            currentNodes = eclose(temp);
        }
        else{
            currentNodes = eclose(currentNodes);
        }
        currentNodes = transit(currentNodes,inputA);
    }
    for(Node* c : eclose(currentNodes)){
        if(c->isAccepting()){
            return true;
        }
    }
    return false;
}

DFA ENFA::toDFA(){
    // Create a new DFA
    DFA dfa;
    // Copy over the alphabet
    dfa.setAlphabet(getAlphabet());
    // Create new containers
    set<Node*> dfaNodes;
    set<Node*> dfaBegin = eclose(beginNodes);
    set<Node*> dfaFinalNodes;
    set<transition*> dfaTransitions;
    // Lazy evaluation begin
    // Create powerset to push to DFA
    set<set<Node*>>newNodes = {eclose(beginNodes)};
    // Create temporary transitions container
    set<transitionNFA*> tempTransitions;
    // Evaluate
    evaluate(newNodes , tempTransitions);
    eliminateExtra(tempTransitions);
    // Sort state
    // Create new states
    for(set<Node*> currentSet : newNodes){
        int count = 0;
        // Create new node
        Node* newNode = new Node();
        string newName;
        bool starting = false;
        bool accepting = false;
        // Create combined name
        newName += "{";
        // Get names of all nodes
        vector<string> names;
        for(Node* currentNode : currentSet){
            // Get new node name
            names.push_back(currentNode->getName());
            // Check if accepting
            if(currentNode->isAccepting()){
                accepting = true;
                }
            // Check if starting
            if(currentSet == dfaBegin){
                starting = true;
                }
            count++;
        }
        // Combine all names
        count = 0;
        sort(names.begin() , names.end());
        for(string n : names){
            newName += n;
            if(count != currentSet.size() - 1){
                newName += ",";
            }
            count++;
        }
        newName += "}";
        // Check all transitions
        for (transitionNFA* t : tempTransitions){
            // Check if transition begins at this set
            if(t->getBeginNodes() == currentSet){
                t->setBeginNodes({newNode});
            }
            // Check if transition ends at this set
            if(t->getEndNodes() == currentSet){
                t->setEndNodes({newNode});
            }
        }
        newNode->setName(newName);
        newNode->setStarting(starting);
        newNode->setAccepting(accepting);
        // Insert the node into the DFA
        dfaNodes.insert(newNode);
        // Check if accepting
        if(newNode->isAccepting()){
            dfaFinalNodes.insert(newNode);
        }
        if(newNode->isStarting()){
            dfaBegin.insert(newNode);
        }
    }
    // Convert all transitions to dfa transitions
    for(transitionNFA* t : tempTransitions){
        dfaTransitions.insert(new transition(*t->getBeginNodes().begin() , *t->getEndNodes().begin() , t->getInput()));
        delete t;
    }
    // Set all the containters to the dfa
    dfa.setNodes(dfaNodes);
    dfa.setBegin(dfaBegin);
    dfa.setFinal(dfaFinalNodes);
    dfa.setTransitions(dfaTransitions);
    return dfa;
}


void ENFA::print(){
   // Make json object
   json j;
   // Set type to NFA
   j["type"] = "ENFA";
   // Set epsilon
   j["eps"] = string(1,ENFA::eps);
   // Add alphabet
   // Make temp vector
   set<string> v_Alphabet;
   for (char c : ENFA::alphabet){
       // Convert char to string and insert into vector
       v_Alphabet.insert(string(1,c));
   }
   j["alphabet"] = v_Alphabet;
   // Add states
   json states_array = json::array();
   for(auto s : nodes){
       // Make new object and add each element of state
       json newObject = json::object();
       newObject["name"] = s->getName();
       newObject["starting"] = s->isStarting();
       newObject["accepting"] = s->isAccepting();
       states_array.push_back(newObject);
   }
   j["states"] = states_array;
   // Add transitions
   json transitions_array = json::array();
   for (auto t : transitions){
       // Make new object and add each element of transition
       json newObject = json::object();
       newObject["from"] = t->getBeginNode()->getName();
       newObject["to"] = t->getEndNode()->getName();
       newObject["input"] = string(1,t->getInput());
       transitions_array.push_back(newObject);
   }
   j["transitions"] = transitions_array;
   // Print to screen
   cout<< setw(4) << j << endl;
}

void ENFA::printStats() {
    // Print number of states
    cout << "no_of_states="<<nodes.size()<<endl;
    // Print all epsilon transitions
    cout << "no_of_transitions[" << eps << "]=" << epsTransitions.size() << endl;
    // Print all the transitions
    for( char c : alphabet){
        int no_transitions = 0;
        for(transition* t : transitions){
            if (t->getInput() == c){
                no_transitions++;
            }
        }
        cout << "no_of_transitions[" << c << "]=" << no_transitions << endl;
    }
    // Get degree : number of transitions from this state. degree[i] = number of states with grade i
    //int degree = 0;
    bool getDegree = true;
    map<int , int> degrees;
    // Loop through states
    for(Node* n : nodes){
        // Get number of transitions
        int node_degree = 0;
        for( transition* t : transitions){
            if (t->getBeginNode() == n){
                // Increase degree
                node_degree++;
            }
        }
        // Insert into map
        degrees[node_degree] += 1;
    }
    // Print all degrees
    for(const auto degree : degrees){
        cout << "degree[" << degree.first << "]=" << degree.second << endl;
    }
}

ENFA::~ENFA()
{
    for(auto n : nodes){
        delete n;
    }
    for(auto t : transitions){
        delete t;
    }
}
