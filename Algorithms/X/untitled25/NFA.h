//
// Created by nr1sl on 3/29/2022.
//
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include "DFA.h"
using namespace  std;
#ifndef UNTITLED25_EVENNFA_H
#define UNTITLED25_EVENNFA_H


class NFA {
    map<string, map<string, set<string>>>states;
    map<set<string>, map<string, set<string>>>dfa;
    vector<string> accepting;
    string current;
    bool erinbool;
    vector<set<string>> erin;
    set<string> dfacurrent;
    vector<string>alphabet;
public:
    NFA(string file);
    bool accepts(string const& code);
    void set_settings_state(string const& state, string character_voor_transitie, string const& toGoPlace);
    map<string, map<string, string>> print();
    void help(set<string> temp);
    DFA toDFA();
};


#endif //UNTITLED25_EVENNFA_H
