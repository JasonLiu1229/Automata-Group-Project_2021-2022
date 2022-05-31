//
// Created by nr1sl on 2/18/2022.
//

#ifndef UNTITLED25_DFA_H
#define UNTITLED25_DFA_H


#include <iostream>
#include <map>
#include <vector>
#include <set>
using namespace  std;

class DFA {
    string alles;
    map<pair<string,string>,bool> geweest;
    map<pair<string,string>,int> indexpositie;
    int indexen;
    map<string, map<string, string>>states;
    map<vector<string>, map<string, vector<string>>>todfa;
    vector<vector<string>> setofstates;
    vector<string> accepting;
    string current;
    set<string>allestate;
    vector<vector<string>>equivalent;
    map<string,vector<vector<string>>>verdeeld;
    vector<vector<string>> erin;
    vector<vector<string>> equivalentin;
    vector<string>alphabet;
    vector<string>toaccept;
    vector<string> onder;
    vector<string> boven;
public:
    DFA();
    void hulp(DFA dfa1, DFA dfa2,vector<string> newstates);
    DFA(vector<string>az,string str,vector<string> acc);
    DFA(const DFA& dfa1,const DFA& dfa2, bool True);
    explicit DFA(const string& file);
    bool accepts(string const& code);
    void set_settings_state(string const& state, const string& character_voor_transitie, string const& toGoPlace);
    void print();
    map<string, map<string, string>>snelprint(bool True);
    DFA minimize();
    void minimizeHulp(vector<string>temp);
    bool juist(vector<string>even,vector<string>e);
    void printTable();
    void printer();
    void helplast();
    void toRegex(string curent,string even,vector<string> gonethere);
    string getcurrent();
    bool yeah(vector<string> alpha, string staat);
    bool done(string plaats);
    string hehhehehe(string curr, string even);
    bool back(string end,string alpha,string vorige);
};


#endif //UNTITLED25_DFA_H
