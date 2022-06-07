#include "DFA.h"
#include "Node.h"
#include "transition.h"
#include "transitionNFA.h"
#include <fstream>
#include <iomanip>
#include "json.hpp"
using namespace std;

using json = nlohmann::json;

DFA::DFA(string filename)
{
    // inlezen uit file
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
        transitions.insert(newTransition);
    }
    // Create beginning TFA table
    createTable();
}

DFA::DFA(DFA &dfa1, DFA &dfa2 , bool intersect) {
    // Copy alphabet
    for( char c : dfa1.getAlphabet() ){
        alphabet.insert(c);
    }
    for( char c : dfa2.getAlphabet() ){
        alphabet.insert(c);
    }
    // Set begin state as the pair of both begin states
    beginNodes.insert( *dfa1.getBegin().begin() );
    beginNodes.insert( *dfa2.getBegin().begin() );
    // Copy all the nodes
    for( Node* n : dfa1.getNodes() ){
        nodes.insert(n);
    }
    for( Node* n : dfa2.getNodes() ){
        nodes.insert(n);
    }
    // Copy all the transitions
    for( transition* t : dfa1.getTransitions() ){
        transitions.insert(t);
    }
    for( transition* t : dfa2.getTransitions() ){
        transitions.insert(t);
    }
    // Begin lazy evaluation
    set<transitionNFA*> tempTransitions;
    set<set<Node*>> newNodes = {beginNodes};
    evaluate(newNodes , tempTransitions);
    eliminateExtra(tempTransitions);
    // Reset nodes
    beginNodes.clear();
    nodes.clear();
    transitions.clear();
    // Create new states
    for(set<Node*> currentSet : newNodes){
        int count = 0;
        // Create new node
        Node* newNode = new Node();
        string newName;
        // Both states must be starting
        bool starting = true;
        // Intersection: initialize true
        bool accepting = intersect;
        
        // Create combined name
        newName += ")";
        // Add each nodes name
        //vector<string> names;
        for(Node* currentNode : currentSet){
            // Get new node name
            newName += currentNode->getName();
            if(count != currentSet.size() - 1){
                newName += ",";
                }
            else{
                newName += "(";
                }
            // If union: one accepting = accepting
            if(!currentNode->isStarting()){
                starting = false;
            }
            // Check if accepting
            // If union: one accepting = accepting
            if(!intersect && currentNode->isAccepting()){
                accepting = true;
            }
            // If intersection: one not accepting = not accepting
            else if(intersect && !currentNode->isAccepting()){
                accepting = false;
            }
            count++;
            }
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
        reverse(newName.begin() , newName.end());
        newNode->setName(newName);
        newNode->setStarting(starting);
        newNode->setAccepting(accepting);
        // Insert the node into the DFA
        nodes.insert(newNode);
        // Check if starting
        if(newNode->isStarting()){
            beginNodes.insert(newNode);
            }
        if(newNode->isAccepting()){
            finalNodes.insert(newNode);
            }
        
    }
    // Convert all transitions to dfa transitions
    transition* nt;
    for(transitionNFA* t : tempTransitions){
        nt = new transition(*t->getBeginNodes().begin() , *t->getEndNodes().begin() , t->getInput());
        transitions.insert(nt);
        delete t;
    }
    // Create beginning TFA table
    createTable();
}

DFA::DFA() : alphabet({}) , nodes({}) , beginNodes({}) , finalNodes({}) , transitions({}) , table({}){}

set<char> DFA::getAlphabet() const{
    return DFA::alphabet;
}
set<Node*> DFA::getNodes() const{
    return DFA::nodes;
}
set<Node*> DFA::getFinal() const{
    return DFA::finalNodes;
}
set<Node*> DFA::getBegin() const{
    return DFA::beginNodes;
}

set<transition*> DFA::getTransitions() const{
    return DFA::transitions;
}
void DFA::setAlphabet(set<char>newAlphabet){
    DFA::alphabet = newAlphabet;
}
void DFA::setNodes(set<Node*>newNodes){
    DFA::nodes = newNodes;
}
void DFA::setFinal(set<Node*>newFinalNodes){
    DFA::finalNodes = newFinalNodes;
}
void DFA::setBegin(set<Node*>newBeginNodes){
    DFA::beginNodes = newBeginNodes;
}

void DFA::setTransitions(set<transition*>newTransitions){
    DFA::transitions = newTransitions;
}

void DFA::evaluate(set<set<Node*>> &newNodes , set<transitionNFA*> &tempTransitions) {
    bool evaluate = true;
    // Create containers
    transitionNFA* newTransition;
    while(evaluate){
        // Remember old size
        int oldSize = static_cast<int>(newNodes.size());
        // Loop through all node pairs
        for(set<Node*> currentNodes : newNodes){
            // Remember beginning
            set<Node*> oldTemp;
            // Loop through the alphabet
            for( char c: alphabet){
                // Loop through both nodes
                for(Node* tempNode : currentNodes){
                    // Add end node of transition
                    oldTemp.insert( transit(tempNode , c ) );
                }
                // Add newly acquired pair
                newNodes.insert(oldTemp);
                // Add transitions
                if(!oldTemp.empty()){
                    // Add used transitions
                    newTransition = new transitionNFA();
                    newTransition->setBeginNodes(currentNodes);
                    // Add end nodes to transition
                    newTransition->setEndNodes(oldTemp);
                    newTransition->setInput(c);
                    // Add transition to container
                    tempTransitions.insert(newTransition);
                }
                // Reset the new node
                oldTemp.clear();
            }
        }
        evaluate = oldSize != newNodes.size();
    }
}

void DFA::eliminateExtra(set<transitionNFA*> &currentSet){
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

void DFA::eliminateExtra(set<transition*>&trans){
    for (auto it1 = trans.begin(); it1 != trans.end(); it1++){
        for (auto it2 = trans.begin(); it2 != trans.end(); it2++){
            if(it1 == it2){
                continue;
            }
            // Check for duplicate
            auto t1 = *it1;
            auto t2 = *it2;
            Node* b1 = t1->getBeginNode();
            Node* e1 = t1->getEndNode();
            Node* b2 = t2->getBeginNode();
            Node* e2 = t2->getEndNode();
            char c1 = t1->getInput();
            char c2 = t2->getInput();
            if( b1 == b2 && e1 == e2 && c1 == c2 ){
                delete t2;
                it2 = trans.erase(it2);
            }
        }
    }
}

Node* DFA::transit(Node* begin , char a){
    if(alphabet.find(a) == alphabet.end()){
        return nullptr;
    }
    for(transition* t : transitions){
        if(t->getBeginNode() == begin && t->getInput() == a){
            return t->getEndNode();
        }
    }
    return begin;
}

bool DFA::accepts(string A){
    Node* currentNode = *beginNodes.begin();
    for(char inputA : A){
        currentNode = transit(currentNode,inputA);
        if(currentNode == nullptr){
            return false;
        }
    }
    return currentNode->isAccepting();
}

void DFA::print(){
   // Make json object
   json j;
   // Set type to DFA
   j["type"] = "DFA";
   // Add alphabet
   set<string> v_Alphabet;
   for (char c : DFA::alphabet){
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

void DFA::createTable(){
    // Create empty sets
    set<string> newSet;
    set<Node*> newMarked;
    // Crossed?
    bool diff;
    // Create all the pairs
    for(Node* n : nodes){
        for(Node* m : nodes){
            // Get pair's names
            newSet.insert(n->getName());
            newSet.insert(m->getName());
            // Get pair's states
            newMarked.insert(n);
            newMarked.insert(m);
            if(newSet.size() == 2){
                diff = ( ( n->isAccepting() && !m->isAccepting() ) || ( !n->isAccepting() && m->isAccepting() ) );
                table[newSet] = diff;
                if(diff){
                    markedPairs.insert( newMarked );
                }
            }
            // Reset sets
            newSet = {};
            newMarked = {};
        }
    }
}

DFA DFA::minimize(){
    // Create new empty DFA and containers for it
    DFA newDFA = DFA();
    set<Node*> newDFA_nodes;
    set<transition*> newDFA_transitions;
    set<Node*> newDFA_final;
    set<Node*> newDFA_begin;
    // Set alphabet
    newDFA.setAlphabet(alphabet);
    // Copy the transitions
    for(auto t : transitions){
        newDFA_transitions.insert(new transition(t));
    }
    // Execute TFA
    fillTable();
    // Get all equivalent sets of states
    set<set<Node*>> newStates;
    set<Node*> newSet;
    // Create new node and components for it
    Node* newNode;
    string newName;
    bool accepting = false;
    bool starting = false;
    // Get all the unmarked pairs
    set<set<Node*>> unmarked;
    for(auto p : table){
        if(!p.second){
            for(auto n : nodes){
                if(p.first.find(n->getName()) != p.first.end()){
                    newSet.insert(n);
                }
            }
            unmarked.insert(newSet);
            newSet = {};
        }
    }
    // Merge the pairs with common elements
    for(const auto &p : unmarked){
        newSet = p;
        // Check if there is a common element with another set
        for(auto q : unmarked){
            for(auto n : q){
                if(newSet.find(n) != newSet.end()){
                    newSet.insert(q.begin() , q.end());
                    break;
                }
            }
        }
        newStates.insert(newSet);
    }
    // Reset container
    unmarked = {};
    // Get all the marked pairs
    set<Node*> marked = nodes;
    vector<string> names;
    for(auto s : newStates){
        newNode = new Node();
        for(Node* n : s){
            marked.erase(n);
            names.push_back(n->getName());
            // Check if starting
            if(n->isStarting()){
                starting = true;
            }
            if(n->isAccepting()){
                accepting = true;
            }
            // Relink the transitions
            for(auto t : newDFA_transitions){
                if(t->getBeginNode() == n){
                    t->setBeginNode(newNode);
                }
                if(t->getEndNode() == n){
                    t->setEndNode(newNode);
                }
            }
        }
        sort(names.begin() , names.end());
        // Merge the name : {state1,state2}
        newName = "{";
        for(const string &name : names){
            newName += name;
            if(name!= *names.rbegin()){
                newName += ", ";
            }
            else{
                newName += "}";
            }
        }
        // Create new state
        newNode->setName(newName);
        newNode->setStarting(starting);
        newNode->setAccepting(accepting);
        // Insert state into the states vector
        newDFA_nodes.insert(newNode);
        // Reset components
        starting = false;
        accepting = false;
        // Reset container
        names = {};
    }
    // Remove extra transitions
    eliminateExtra(newDFA_transitions);
    // Create new nodes from the marked ones
    for(auto n : marked){
        // Create new node
        newNode = new Node("{" + n->getName() + "}" , n->isStarting() , n->isAccepting());
        newDFA_nodes.insert(newNode);
        // Relink transitions
        for(auto t : newDFA_transitions){
            if(t->getBeginNode() == n){
                t->setBeginNode(newNode);
            }
            if(t->getEndNode() == n){
                t->setEndNode(newNode);
            }
        }
    }
    for(auto n : newDFA_nodes){
        if(n->isStarting()){
            newDFA_begin.insert(n);
        }
        if(n->isAccepting()){
            newDFA_final.insert(n);
        }
    }
    newDFA.setNodes(newDFA_nodes);
    newDFA.setTransitions(newDFA_transitions);
    newDFA.setBegin(newDFA_begin);
    newDFA.setFinal(newDFA_final);
    return newDFA;
}

set<set<Node*>> DFA::findTransition(set<Node*> &beginNodes , char c){
    // Find a pair of nodes that transits to the given set with char c
    set<Node*> tempNode = {};
    set<Node*> newSet;
    set< set<Node*> > newNode;
    for(auto n : nodes){
        for(auto m : nodes){
            tempNode.insert(transit(n , c));
            tempNode.insert(transit(m , c));
            if( tempNode == beginNodes){
                newSet.insert(n);
                newSet.insert(m);
                newNode.insert(newSet);
            }
            // Reset tempNode
            tempNode = {};
            newSet = {};
        }
    }
    return newNode;
}

void DFA::fillTable(){
    bool evaluate = true;
    set< set<Node*> > newPair;
    set<string> newNames;
    vector<string> newMarked;
    set<Node*> tempPair;
    Node* newB;
    Node* newE;
    int oldSize;
    while(evaluate){
        // Remember old size
        oldSize = static_cast<int>(markedPairs.size());
        // Loop through marked pairs
        for(auto p : markedPairs){
            // Loop through alphabet
            for(char c : alphabet){
                // Find a transition to this marked pair
                newPair = findTransition(p , c);
                // Check if transition is valid
                for(const auto &newP : newPair){
                    // Get first and second node of the pair
                    newB = *newP.begin();
                    newE = *newP.rbegin();
                    // Get node names
                    newMarked.push_back(newB->getName());
                    newMarked.push_back(newE->getName());
                    sort(newMarked.begin() , newMarked.end());
                    newNames.insert(newMarked.begin() , newMarked.end());
                    // Insert new pair into markedPairs set
                    markedPairs.insert(newP);
                    // Insert new pair names into table
                    table[newNames] = true;
                    // Reset containers
                    newMarked = {};
                    newNames = {};
                }
                // Reset pairs
                newPair = {};
                tempPair = {};
            }
        }
        // Evaluate?
        evaluate = (oldSize != markedPairs.size());
    } 
}

void DFA::printTable(){
   vector<string> tempNodes;
   for(auto n : nodes){
       tempNodes.push_back( n->getName() );
   }
   sort( tempNodes.begin() , tempNodes.end() );
   int count = 1;
   // Loop from 2nd element to last element
   for(int i = 1; i < tempNodes.size(); i++){
       // Print row name
       cout << tempNodes[i] << '\t';
       // Loop until count
       for(int j = 0; j < count; j++){
           if( table[ { tempNodes[i] , tempNodes[j] }] ){
               cout << 'X' << '\t';
           }
           else{
               cout << '-' << '\t';
           }
       }
       cout << endl;
       count++;
   }
   cout << '\t';
   for(int i = 0; i < tempNodes.size() - 1; i++){
       cout << tempNodes[i];
       if(i != tempNodes.size() - 1){
           cout << '\t';
       }
   }
   cout << endl;
}

bool DFA::operator==(DFA &dfa2){
    // Save original nodes and transitions
    set<Node*> originalNodes = nodes;
    set<transition*> originalTransitions = transitions;
    // Get all the nodes from both DFAs
    for(auto n : dfa2.getNodes()){
        nodes.insert(n);
    }
    for(auto t : dfa2.getTransitions()){
        transitions.insert(t);
    }
    // Execute TFA
    createTable();
    fillTable();
    // Print filled table
    printTable();
    // Check whether the pair of begin nodes has been filled
    Node* b1 = *getBegin().begin();
    Node* b2 = *dfa2.getBegin().begin();
    // Reset the nodes and transitions
    nodes = originalNodes;
    transitions = originalTransitions;

    return !table[ { b1->getName() , b2->getName() } ];
}

DFA::~DFA()
{
    for(auto n : nodes){
        delete n;
    }
    for(auto t : transitions){
        delete t;
    }
}
