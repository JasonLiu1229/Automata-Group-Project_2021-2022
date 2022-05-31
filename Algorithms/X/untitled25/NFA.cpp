#include <iostream>
#include <fstream>
#include <iomanip>
#include <iterator>
#include "json.hpp"
#include "NFA.h"
#include "iomanip"
using json = nlohmann::json;
using namespace::std;

NFA::NFA(string file){
    ifstream input(file);
    json j;
    input >> j;
    alphabet = j["alphabet"].get<vector<string>>();
    for(auto i:j["states"]){
        if(i["starting"]){
            current = i["name"];
        }
        else if(i["accepting"]){
            accepting.push_back(i["name"]);
        }
    }
    for(auto i:j["transitions"]){
        set_settings_state(i["from"],i["input"],i["to"]);
    }
}

void NFA::set_settings_state(const string &state, string character_voor_transitie, const string &toGoPlace) {
    states[state][character_voor_transitie].insert(toGoPlace);
}

DFA NFA::toDFA(){
    vector<set<string>> even;
    dfacurrent.insert(current);
    erin.push_back(dfacurrent);
    for (auto i: alphabet) {
        if(!states[current][i].empty()){
            dfa[dfacurrent][i] = states[current][i];
            even.push_back(dfa[dfacurrent][i]);
            erin.push_back(dfa[dfacurrent][i]);
        }
    }
    for(auto i:even){
        help(i);
    }
    current = "{" + current + "}";
    map<string, map<string, string>> temp = print();
    DFA dfa(alphabet,current,accepting);
    for(auto i:temp){
        for(auto j:i.second)
            dfa.set_settings_state(i.first,j.first,j.second);
    }
    return dfa;
}

void NFA::help(set<string> temp) {
    vector<set<string>> even;
    set<string>tempo;
    for(auto l:alphabet) {
        bool in = false;
        tempo.clear();
        for (auto i: temp) {
            for (auto k: states[i][l]) {
                tempo.insert(k);
            }
        }
        for (const auto &j: erin) {
            if (tempo == j) {
                dfa[temp][l] = tempo;
                in = true;
                break;
            }
        }
        if (!tempo.empty() and !in) {
            dfa[temp][l] = tempo;
            even.push_back(tempo);
        }
    }
    for(auto i:even){
        erin.push_back(i);
    }
    if(even.empty()){
        return;
    }
    else{
        for(auto i:even){
            help(i);
        }
    }
}


map<string, map<string, string>> NFA::print() {
    map<string, map<string, string>>kstates;
    set<string>::iterator itr;
    for (const auto &i: dfa) {
        string fwoorden;
        for (itr = i.first.begin(); itr != i.first.end(); itr++) {
            if (itr == i.first.begin()) {
                fwoorden += "{" + *itr;
            } else {
                fwoorden += "," + *itr;
            }
        }
        fwoorden += "}";
        for (const auto &j: i.second) {
            string swoorden;
            for (itr = j.second.begin(); itr != j.second.end(); itr++) {
                if (itr == j.second.begin()) {
                    swoorden += "{" + *itr;
                } else {
                    swoorden += "," + *itr;
                }
            }
            swoorden += "}";
            kstates[fwoorden][j.first]=swoorden;
        }

    }
    vector<string>temp;
    for(auto plaats:accepting){
        for(auto i:erin){
            for(auto j:i){
                if(j == plaats){
                    string swoord;
                    for (itr = i.begin(); itr != i.end(); itr++) {
                        if (itr == i.begin()) {
                            swoord += "{" + *itr;
                        } else {
                            swoord += "," + *itr;
                        }
                    }
                    swoord += "}";
                    temp.push_back(swoord);
                    break;
                }
            }
        }
    }
    accepting = temp;
    return kstates;
}