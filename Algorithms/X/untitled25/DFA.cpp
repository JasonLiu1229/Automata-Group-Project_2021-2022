#include <iostream>
#include <fstream>
#include <iomanip>
#include "json.hpp"
#include "DFA.h"
using namespace::std;
using json = nlohmann::json;

DFA::DFA() = default;

DFA::DFA(vector<string>az,string str,vector<string> acc){
    alphabet = az;
    current = str;
    accepting = acc;
    indexen =0;
}

DFA::DFA(const DFA& dfa1, const DFA& dfa2, bool True){
    vector<string> newbegin;
    indexen =0;
    newbegin.push_back(dfa1.current);
    newbegin.push_back(dfa2.current);
    erin.push_back(newbegin);
    alphabet = dfa1.alphabet;
    hulp(dfa1,dfa2,newbegin);

    for(const auto& i:dfa1.accepting){
        toaccept.push_back(i);
    }
    for(const auto& i:dfa2.accepting){
        toaccept.push_back(i);
    }
    map<string, map<string, string>> temp = snelprint(True);
    for(const auto& i:temp) {
        for (const auto& j: i.second) {
            if (i == *temp.begin()){
                current = i.first;
            }
            set_settings_state(i.first, j.first, j.second);
        }
    }
}

void DFA::hulp(DFA dfa1, DFA dfa2,vector<string> newstates){
    vector<vector<string>> even;
    for(const auto& a:alphabet){
        bool in= false;
        vector<string> tempo;
        tempo.push_back(dfa1.states[newstates[0]][a]);
        tempo.push_back(dfa2.states[newstates[1]][a]);
        for(const auto&k:erin){
            if(tempo == k){
                todfa[newstates][a] = tempo;
                in = true;
                break;
            }
        }
        if(!in){
            even.push_back(tempo);
            todfa[newstates][a] = tempo;
        }
    }
    if(even.empty()){
        return;
    }
    for(const auto& i:even){
        erin.push_back(i);
    }
    for(const auto& i:even){
        hulp(dfa1,dfa2,i);
    }
}

DFA::DFA(const string& file){
    indexen =0;
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
void DFA::set_settings_state(const string &state, const string& character_voor_transitie, const string &toGoPlace) {
    states[state][character_voor_transitie] = toGoPlace;
    allestate.insert(state);
}
bool DFA::accepts(string const& code) {
    for (char i : code){
        string k;
        k.push_back(i);
        for(const auto& j:alphabet){
            if(j == k){
                break;
            }
            else if (j==alphabet.back()){
                return false;
            }
        }
        current = states[current][k];
        }
    for (const auto& plaats:accepting){
        if (plaats== current){
            return true;
        }
    }
    return false;
}

void DFA::print() {
    json file;
    map<string, string> even;
    map<string, vector<string>> alfabet;
    for (const auto &i: states) {
        even["from"] = i.first;
        for (const auto &j: i.second) {
            even["to"] = j.second;
            even["input"] = j.first;
            file["transitions"].push_back(even);
        }
    }
    json eventjes;
    for (const auto& i: states) {
        if (i.first == current) {
            eventjes["name"] = i.first;
            eventjes["starting"] = true;
            eventjes["accepting"] = false;
            file["states"].push_back(eventjes);
            continue;
        }
        bool True = true;
        for (const auto& plaats: accepting) {
            if (i.first == plaats) {
                eventjes["name"] = i.first;
                eventjes["starting"] = false;
                eventjes["accepting"] = true;
                file["states"].push_back(eventjes);
                True = true;
                break;
            } else {
                True = false;
            }
        }
        if (!True) {
            eventjes["name"] = i.first;
            eventjes["starting"] = false;
            eventjes["accepting"] = false;
            file["states"].push_back(eventjes);
        }
    }
    file["alphabet"] = alphabet;
    file["type"] = "DFA";
    cout << setw(4) << file << endl;
}
map<string, map<string, string>> DFA::snelprint(bool True) {
    map<string, map<string, string>>kstates;
    for (const auto &i: todfa) {
        string fwoorden;
        for (int it=0;it<i.first.size();it++) {
            if (it == 0) {
                fwoorden += "(" + i.first[it];
            } else {
                fwoorden += "," + i.first[it];
            }
        }
        fwoorden += ")";
        for (const auto &j: i.second) {
            string swoorden;
            for (int it=0;it<j.second.size();it++) {
                if (it == 0) {
                    swoorden += "(" + j.second[it];
                } else {
                    swoorden += "," + j.second[it];
                }
            }
            swoorden += ")";
            kstates[fwoorden][j.first]=swoorden;
        }
    }
    vector<string>temp;
    if(!True){
        for(const auto& it:toaccept){
            for(auto e:erin){
                for(const auto& i:e){
                    if(i == it){
                        string accept;
                        for(int f=0;f<e.size();f++){
                            if(f == 0){
                                accept += "(" + e[f];
                            }
                            else{
                                accept += "," + e[f];
                            }
                        }
                        accept+= ")";
                        temp.push_back(accept);
                        break;
                    }
                }
            }
        }
    }
    else{
        string accept = "(";
        for(int it=0;it<toaccept.size();it++) {
            if(it==0){
                accept += toaccept[it];
            }
            else{
                accept +=","+ toaccept[it];
            }
        }
        accept+= ")";
        temp.push_back(accept);
    }
    accepting = temp;
    return kstates;
}





DFA DFA::minimize(){
    for(auto i:states){
        if(i.first == states.begin()->first){
            onder.push_back(i.first);
            continue;
        }
        else if(i.first == states.rbegin()->first){
            boven.push_back(i.first);
            break;
        }
        else{
            onder.push_back(i.first);
            boven.push_back(i.first);
        }
    }
    for(auto i:accepting){
        for(auto l:states){
            bool in =false;
            vector<string> even;
            for(auto c: accepting){
                if(c==l.first){
                    in = true;
                    break;
                }
            }
            if(!in){
                even.push_back(i);
                even.push_back(l.first);
                setofstates.push_back(even);
                erin.push_back(even);
            }
        }
    }
    for(auto i:setofstates){
        minimizeHulp(i);
    }
    for(auto i:allestate){
        vector<string>even;
        even.push_back(i);
        for(auto a:allestate){
            bool in = false;
            even.push_back(a);
            for(auto e:erin){
                if(juist(e,even)){
                    in = true;
                    break;
                }
            }
            if(!in && even[0] !=even[1]){
                verdeeld[a].push_back(even);
                equivalent.push_back(even);
                erin.push_back(even);
                even.clear();
                even.push_back(i);
            }
            even.clear();
            even.push_back(i);
        }
    }
    printer();
    return *this;
}




void DFA::printer(){
    vector<string>gone;
    map<string,vector<string>> yes;
    for(auto o:allestate){
        bool in= false;
        for(auto g:gone){
            if(g==o){
                in= true;
                break;
            }
        }
        if(!in){
            bool goed= false;
            for(auto i:allestate){
                vector<string>tempo = {o,i};
                for(auto p:equivalent){
                    if(p==tempo){
                        yes[o].push_back(i);
                        gone.push_back(i);
                        goed = true;

                    }
                }
            }
            if(goed){
                yes[o].push_back(o);
                equivalentin.push_back(yes[o]);
            }
        }
    }
    for(auto alle:allestate){
        bool ja= false;
        vector<vector<string>> eventjes = equivalentin;
        for(auto i:eventjes){
            for(auto er:i){
                if(er == alle){
                    ja = true;
                    break;
                }
            }
            if(!ja){
                vector<string>st;
                st.push_back(alle);
                equivalentin.push_back(st);
                break;
            }
        }
    }
    for(auto &i:equivalentin){
        set<string>automatich;
        for(auto e:i){
            automatich.insert(e);
        }
        vector<string>terug;
        for(auto e:automatich){
            terug.push_back(e);
        }
        i=terug;
    }

    bool afbreken = false;
    for(auto i:equivalentin){
        for(auto j:i){
            if(j==current){
                current.clear();
                current += "{";
                if(i.size()==1){
                    current += i[0] + "}";
                    afbreken = true;
                    break;
                }
                else{
                    for(auto k:i){
                        if(k!=i[i.size()-1]){
                            current+= k+",";
                        }
                        else{
                            current+= k;
                        }
                    }
                    current+= "}";
                    afbreken = true;
                    break;
                }
            }
        }
        if(afbreken){
            break;
        }
    }
    helplast();
    vector<string>tem;
    for(auto i:equivalentin){
        for(auto l:accepting){
            for(auto k:i){
                if(k==l){
                    string woord = "{";
                    if(i.size() ==1){
                        woord += i[0] + "}";
                    }
                    else{
                        for(auto m:i){
                            if(m !=i[i.size()-1]){
                                woord += m +",";
                            }
                            else{
                                woord +=m;
                            }
                        }
                        woord+="}";
                    }
                    tem.push_back(woord);

                }
            }
        }
    }
    accepting = tem;
}
string DFA::getcurrent(){
    return current;
}


void DFA::helplast(){
    map<string, map<string, string>> temp = states;
    states.clear();
    for(auto e:equivalentin){
        for(auto a:alphabet){
            bool done = false;
            for(auto e2: equivalentin){
                for(auto i:e2){
                    string word = i;
                    for(auto s:e){
                        if(word == temp[s][a]){
                            string from = "{";
                            if(e.size() == 1){
                                from += e[0] +"}";
                            }
                            else if(e.size()>1){
                                for(auto k:e){
                                    if(k !=e[e.size()-1]){
                                        from += k + ", ";
                                    }
                                    else{
                                        from += k;
                                    }

                                }
                                from +="}";
                            }
                            string to = "{";
                            if(e2.size() ==1){
                                to += e2[0] + "}";
                            }
                            else if(e2.size()>1){
                                for(auto l:e2){
                                    if(l!=e2[e2.size()-1]){
                                        to+= l + ", ";
                                    }
                                    else{
                                        to+= l;
                                    }
                                }
                                to+= "}";
                            }
                            states[from][a] = to;
                            done = true;
                            break;
                        }
                    }
                    if(done){
                        break;
                    }
                }
                if(done){
                    break;
                }
            }
        }
    }
}

void DFA::printTable(){
    bool run= true;
    int begin = 1;
    int hoogte = 0;
    while(run){
        cout<<boven[hoogte];
        for(int i=0; i<begin;i++){
            bool x= true;
            vector<string>even = {boven[hoogte],onder[i]};
            for(auto e:equivalent){
                if(juist(e,even)){
                    x=false;
                    break;
                }
            }
            if(x){
                cout<< "   X";
            }
            else{
                cout<<"   -";
            }
        }
        cout<<endl;
        hoogte+=1;
        if(begin == boven.size()){
            run = false;
        }
        begin+=1;
    }
    cout<<" ";
    for(auto i:onder){
        cout<< "   "+i;
    }
    cout<<endl;
}



bool DFA::juist(vector<string>even,vector<string>e){
    if(even[0]==e[0] && even[1] == e[1]){
        return true;
    }
    else if(even[1]==e[0] && even[0]==e[1]){
        return true;
    }
    return false;
}
void DFA::minimizeHulp(vector<string>temp){
    vector<vector<string>> temporary;
    vector<string> tempo;
    for(auto a:alphabet){
        for(auto i:states){
            if(i.second[a]== temp[0]){
                tempo.push_back(i.first);
                for(auto s:states){
                    if(s.second[a]==temp[1]){
                        bool in = false;
                        tempo.push_back(s.first);
                        for(auto e:erin){
                            if(juist(e,tempo)){
                                in = true;
                                tempo.clear();
                                tempo.push_back(i.first);
                                break;
                            }
                        }
                        if(!in && tempo[0] != tempo[1]){
                            temporary.push_back(tempo);
                            erin.push_back(tempo);
                            tempo.clear();
                            tempo.push_back(i.first);
                        }
                    }
                }
            }
        }
    }
    if(temporary.empty()){
        return;
    }
    else{
        for(auto i:temporary){
            minimizeHulp(i);
        }
    }
}
bool DFA::yeah(vector<string> alpha, string staat){
    bool yeah = true;
    for(auto i:alpha){
        if(states[staat][i] != staat){
            yeah = false;
        }
    }
    return yeah;
}

bool DFA::done(string plaats){
    for(auto i:accepting){
        if(i==plaats){
            return true;
        }
    }
    return false;
}
bool double2( vector<string> vec, string str){
    for(auto i:vec){

    }
}
bool doublecheck(vector<string> vec, string str){
    for(auto i:vec){
        if(i == str){
            return true;
        }
    }
    return false;
}
bool DFA::back(string end,string alpha,string vorige){
    for(auto i:accepting){
        if(end == i){
            if(states[end][alpha] == vorige){
                return true;
            }
        }
    }
    return false;
}
string curren;
string even2;
bool zijner;

void DFA::toRegex(string curr, string even,vector<string> gonethere){
    if(zijner  && curren == curr){
        even = even2;
        zijner = true;
    }
    string zichzelf = "(";
    if(yeah(alphabet,current) && !accepts(curr)){
        return;
    }
    else if(done(curr)){
        vector<string> alpha;
        int size = (int) even.size();
        int check = 0;
        if(yeah(alphabet,curr)){
            even += "(";
            for(auto i:alphabet){
                even+= i + "+";
            }
            even.pop_back();
            even +=")*";
        }
        else{
            int indexenalpha = 0;
            for(auto i:alphabet){
                if(states[curr][i] == curr && check ==0){
                    even += "(" + i;
                    indexenalpha++;
                    check++;
                }
                else if(indexenalpha == alphabet.size()-1 && states[curr][i] == curr){
                    even += i + ")*";
                    indexenalpha++;
                }
                else if(indexenalpha == alphabet.size()-1 && states[curr][i] != curr && even.size() !=size){
                    even += ")*";
                }
                else if(check ==1 && states[curr][i] == curr){
                    even += i;
                    indexenalpha++;
                }
                else{
                    alpha.push_back(i);
                }
            }
        }
        alles += even + "+";
        if(!alpha.empty()){
            for(auto i:alpha){
                if(doublecheck(gonethere,curr)){
                    string tempo;
                    for(int k =0; k<even.size();k++){
                        if(k == indexpositie[{curr,i}]){
                            tempo += "(";
                            tempo+= even[k];
                        }
                        else{
                            tempo+= even[k];
                        }
                    }
                    tempo += ")*";
                    even = tempo;
                    zijner = true;
                    even2 = even;
                    return;
                }
                if(!yeah(alphabet,states[curr][i])){
                    even += i;
                }
                geweest[{curr,i}] = true;

                indexpositie[{curr,i}] = indexen;
                indexen++;
                toRegex(states[curr][i],even,gonethere);

            }
        }
    }
    else{
        vector<string> over;
        for(auto i:alphabet){
            if(states[curr][i] == curr){
                zichzelf+=i + "+";
            }
            else{
                over.push_back(i);
            }
        }
        if(zichzelf.size() !=1){
            zichzelf.pop_back();
            zichzelf +=")*";
            even += zichzelf;
        }
        for(const auto& i:over){
            if(back(states[curr][i],i,curr)){
                even += "(" + i + i + ")*";
            }
            if(doublecheck(gonethere,curr)){
                string tempo;
                for(int k =0; k<even.size();k++){
                    if(k == indexpositie[{curr,i}]){
                        tempo += "(";
                        tempo+= even[k];
                    }
                    else{
                        tempo+= even[k];
                    }
                }
                tempo += ")*";
                even = tempo;
                zijner = true;
                even2 = even;
                return;
            }
            else{
                if(!yeah(alphabet,states[curr][i]) || done(states[curr][i])){
                    even += i;
                }
                geweest[{curr,i}] = true;
                gonethere.push_back(curr);
                indexpositie[{curr,i}] = indexen;
                indexen++;
                toRegex(states[curr][i],even,gonethere);
                if(zijner  && curren != curr){
                    return;
                }
                if(zijner  && curren == curr){
                    even = even2;
                    zijner = false;
                    continue;
                }
                gonethere.pop_back();
                even.pop_back();
            }
        }
    }
}

string DFA::hehhehehe(string curr, string even){
    toRegex(curr,even,{});
    alles.pop_back();
    return alles;
}
