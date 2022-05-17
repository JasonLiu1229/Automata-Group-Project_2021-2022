#include <iostream>
#include <fstream>
#include <iomanip>
#include "../json.hpp"
#include <vector>
using namespace std;

using json = nlohmann::json;

int main(){
    // inlezen uit file
    ifstream input("DFA.json");
    vector<char>al;
    json j;
    input >> j;
    string s = j.dump();
    for (json::iterator it = j.begin(); it != j.end(); ++it) {
        if(it.key() == "alphabet"){
          vector<string> a = it.value();
        }
    }
    // tonen op het scherm
    cout << setw(4) << j << endl;
    // manueel aanmaken
    return 0;
}