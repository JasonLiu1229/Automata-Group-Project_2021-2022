// custom libs
#include "Maze.h"
#include "Path.h"
#include "json.hpp"
#include "Parser.h"

// c++ libs
#include <utility>
#include <fstream>
#include <iomanip>

using namespace std;
using json = nlohmann::json;

Maze::Maze(const string &fileName) :levelName(fileName), status(play) , key_count(0), savedFile("") {
    Parser jsonParser(fileName);
    levelName = jsonParser.getTxt_Filename();
    loadGame(levelName);
}

Maze::Maze(): key_count(0){
}

// read level

void Maze::tileConfig(Path* &leftTile, Path* &rightTile, int i, int j){
    if (j == 0){
        rightTile = nullptr;
        leftTile = this->at(i).at(j-1);
    }
    else if (j == height - 1){
        leftTile = nullptr;
        rightTile = this->at(i).at(j-1);
    }
    else {
        leftTile = this->at(i).at(j+1);
        rightTile = this->at(i).at(j-1);
    }
}

bool Maze::generateMaze(const string &filename) {
    ifstream txtParser;
    txtParser.open(LEVDIR + filename);
    // make path
    if (txtParser.is_open()){
        string line;
        while (getline(txtParser, line)){
            vector<Path*> pathRow;
            for (int i = 0; i < line.size(); ++i) {
                auto* path = new Path();
                char c = line[i];
                if(c == '#'){
                    path->setSettings(wall);
                }
                else if(c == '$'){
                    path->setStarting(true);
                    player = new Player(path, "Name");
                    start = path;
                }
                else if(c == '&'){
                    path->setAccepting(true);
                }
                else if(c == '^'){
                    path->setKey(true);
                    key_count++;
                }
                pathRow.push_back(path);
                allPaths.push_back(path);
            }
            this->push_back(pathRow);
        }

        // Get width and height
        height = static_cast<int>( this->size() );
        width = static_cast<int>( this->at(0).size() );
        // load status of whole game from txt file
        Path* currentTile;
        Path* nextTile;
        for (int i = 0; i < height; i++){
            for (int j = 0; j < width; j++){
                // Get current tile
                currentTile = this->at(i)[j];
                // Get tile above
                // Case: there is no tile above
                if(i == 0){
                    currentTile->setUp(nullptr);
                }
                else{
                    nextTile = this->at(i-1)[j];
                    if(!nextTile->isWall()){
                        currentTile->setUp(nextTile);
                        currentTile->setpath("w",nextTile);
                        currentTile->setmovement("w");
                    }
                }
                // Get tile left
                if(j == 0){
                    currentTile->setLeft(nullptr);
                }
                else{
                    nextTile = this->at(i)[j-1];
                    if(!nextTile->isWall()){
                        currentTile->setLeft(nextTile);
                        currentTile->setpath("a", nextTile);
                        currentTile->setmovement("a");
                    }
                }
                // Get tile right
                if(j == width - 1){
                    currentTile->setRight(nullptr);
                }
                else{
                    nextTile = this->at(i)[j+1];
                    if(!nextTile->isWall()) {
                        currentTile->setRight(nextTile);
                        currentTile->setpath("d", nextTile);
                        currentTile->setmovement("d");
                    }
                }
                // Get tile under
                if(i == height - 1){
                    currentTile->setDown(nullptr);
                }
                else{
                    nextTile = this->at(i+1)[j];
                    if(!nextTile->isWall()) {
                        currentTile->setDown(nextTile);
                        currentTile->setpath("s", nextTile);
                        currentTile->setmovement("s");
                    }
                }
            }
        }
        collectedKeys = new Collectable_DFA(key_count);
    }
    txtParser.close();
    return false;
}

// Getters and setters
int Maze::getWidth() const{
    return width;
}

int Maze::getHeight() const{
    return height;
}

Path* Maze::getPath(int i , int j){
    return this->at(i).at(j);
}

// user interface functions
void Maze::playMaze() {
    // set status on play
    status = play;
}

void Maze::pauseMaze() {
    // set status on pause
    status = pause;
}

void Maze::generateCustom() {
    // set status to custom level
    Maze::customLevel = true;
}

void Maze::saveGame(const string &fileNameInput) {
    // write status of whole game in a txt file
    // TXT file
    fstream saveFile;
    FILE* codefile;

    // create file
    bool exists = false;
    int i = 0;
    string filename;
    filename = fileNameInput;
//    filename += fileNameInput;
    filename += TXT;

    while (!exists){
        i++;
        codefile = fopen(filename.c_str(), "r");
        if (codefile){
//            filename = SVG1;
            filename = fileNameInput;
            filename += '(' + to_string(i) + ')' + TXT;
        }
        else {
            saveFile.open(filename.c_str(), ios::app | ios::out);
            savedFile = filename;
            exists = true;
        }
    }
    // write in a file
    for (int k = 0; k < width; ++k) {
        for (int j = 0; j < height; ++j) {
            Path* oldPath = this->at(k).at(j);
            if (oldPath->getSettings() == path){
                if (oldPath->isKey()){
                    saveFile << '^';
                }
                else if (oldPath->isStarting()){
                    saveFile << '$';
                }
                else if (oldPath->isAccepting()){
                    saveFile << '&';
                }
                else if (oldPath->isEnemy()){
                    saveFile << '~';
                }
                else {
                    saveFile << '.';
                }
            }
            else if (oldPath->getSettings() == wall){
                saveFile << '#';
            }
        }
        saveFile << '\n';
    }
    saveFile.close();

    // Json
    fstream saveFileJson;
    exists = false;
    string filenameJ;
    filenameJ = fileNameInput;
    filenameJ += JSON;


    i = 0;
    while (!exists){
        i++;
        codefile = fopen(filenameJ.c_str(), "r");
        if (codefile){
            filenameJ = SVG1;
            filenameJ += fileNameInput;
            filenameJ += '(' + to_string(i) + ')' + JSON;
        }
        else {
            saveFileJson.open(filenameJ.c_str(), ios::out);
            exists = true;
        }
    }

    // write in file
    json file;
    file["Level"] = {{"fileName", filename}, {"regex", ""}};
    saveFileJson << std::setw(4) << file << endl;
    saveFileJson.close();
}

void Maze::quickSave() {
    ofstream saveFile;
    saveFile.open(savedFile);
    // write in a file
    for (int k = 0; k < width; ++k) {
        for (int j = 0; j < height; ++j) {
            Path* oldPath = this->at(k).at(j);
            if (oldPath->getSettings() == path){
                if (oldPath->isKey()){
                    saveFile << '^';
                }
                else if (oldPath->isStarting()){
                    saveFile << '$';
                }
                else if (oldPath->isAccepting()){
                    saveFile << '&';
                }
                else {
                    saveFile << '.';
                }
            }
            else if (oldPath->getSettings() == wall){
                saveFile << '#';
            }
        }
        saveFile << '\n';
    }
    saveFile.close();
}

void Maze::Save(const string &fileName) {
    if (savedFile.empty()){
        // hard save
        saveGame(fileName);
    }
    else{
        quickSave();
    }
}

void Maze::loadGame(const string &fileName) {
    string line;
    ifstream gamefile(fileName);
    if(gamefile.is_open()){
        player = new Player();
        while(getline(gamefile,line)){
            vector<Path*> weg;
            for(auto i:line){
                Path* road = new Path();
                if(i == '#'){
                    road->setSettings(wall);
                }
                else if(i=='$'){
                    road->setStarting(true);
                    start = road;
                    player->setCurrentTile(road);
                }
                else if(i=='&'){
                    road->setAccepting(true);
                }
                else if(i == '~'){
                    Enemy* enemy = new Enemy();
                    road->setEnemy(true);
                    enemy->setCurrentTile(road);
                    enemy->train(Training2);
                    enemy->train(Training1);
                    enemies.push_back(enemy);
                }
                else if(i == '^'){
                    road->setKey(true);
                    key_count++;
                }
                weg.push_back(road);
                allPaths.push_back(road);
            }
            this->push_back(weg);
        }
    }
    // Get width and height
    height = static_cast<int>( this->size() );
    width = static_cast<int>( this->at(0).size() );
    // load status of whole game from txt file
    Path* currentTile;
    Path* nextTile;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Get current tile
            currentTile = this->at(i)[j];
            // Get tile above
            // Case: there is no tile above
            if(i == 0){
                currentTile->setUp(nullptr);
                transitions[currentTile] = {UP, currentTile};
            }
            else{
                nextTile = this->at(i-1)[j];
                if(!nextTile->isWall()){
                    currentTile->setUp(nextTile);
                    currentTile->setpath("w",nextTile);
                    currentTile->setmovement("w");
                    transitions[currentTile]= {UP, nextTile};
                }
                else {
                    transitions[currentTile]= {UP, currentTile};
                }
            }
            // Get tile left
            if(j == 0){
                currentTile->setLeft(nullptr);
                transitions[currentTile] = {LEFT, currentTile};
            }
            else{
                nextTile = this->at(i)[j-1];
                if(!nextTile->isWall()){
                    currentTile->setLeft(nextTile);
                    currentTile->setpath("a", nextTile);
                    currentTile->setmovement("a");
                    transitions[currentTile] = {LEFT, nextTile};
                }
                else {
                    transitions[currentTile] = {LEFT, currentTile};
                }
            }
            // Get tile right
            if(j == width - 1){
                currentTile->setRight(nullptr);
                transitions[currentTile] = {RIGHT, currentTile};
            }
            else{
                nextTile = this->at(i)[j+1];
                if(!nextTile->isWall()) {
                    currentTile->setRight(nextTile);
                    currentTile->setpath("d", nextTile);
                    currentTile->setmovement("d");
                    transitions[currentTile] = {RIGHT, nextTile};
                }
                else {
                    transitions[currentTile] = {RIGHT, currentTile};
                }
            }
            // Get tile under
            if(i == height - 1){
                currentTile->setDown(nullptr);
                transitions[currentTile] = {DOWN, currentTile};
            }
            else{
                nextTile = this->at(i+1)[j];
                if(!nextTile->isWall()) {
                    currentTile->setDown(nextTile);
                    currentTile->setpath("s", nextTile);
                    currentTile->setmovement("s");
                    transitions[currentTile] = {DOWN, nextTile};
                }
                else {
                    transitions[currentTile] = {DOWN, currentTile};
                }
            }
        }
    }
    collectedKeys = new Collectable_DFA(key_count);
}

void Maze::simulateMove(movement m) {
    if(player->getCurrentTile() == nullptr){
        return;
    }
    if(m == UP && player->getCurrentTile()->getUp() != nullptr){
        player->GetCurrentTile()->setStarting(false);
        player->SetCurrentTile(player->GetCurrentTile()->getUp());
        player->GetCurrentTile()->setStarting(true);
    }
    else if(m == DOWN && player->getCurrentTile()->getDown() != nullptr){
        player->GetCurrentTile()->setStarting(false);
        player->SetCurrentTile(player->GetCurrentTile()->getDown());
        player->GetCurrentTile()->setStarting(true);
    }
    else if(m == LEFT && player->getCurrentTile()->getLeft() != nullptr){
        player->GetCurrentTile()->setStarting(false);
        player->SetCurrentTile(player->GetCurrentTile()->getLeft());
        player->GetCurrentTile()->setStarting(true);
    }
    else if(m == RIGHT && player->getCurrentTile()->getRight() != nullptr){
        player->GetCurrentTile()->setStarting(false);
        player->SetCurrentTile(player->GetCurrentTile()->getRight());
        player->GetCurrentTile()->setStarting(true);
    }
    if(player->GetCurrentTile()->isKey()){
        collectedKeys->setCurrentState(collectedKeys->getCurrentState()->getNext());
        collectedKeys->done();
        player->GetCurrentTile()->setKey(false);
        key_count--;
    }
}

Player* Maze::getPlayer() {
    return player;
}

Collectable_DFA* Maze::getDFAkeys() {
    return collectedKeys;
}

bool Maze::checkmaze(Path* richting){
    if(richting->isEnemy()){
        return true;
    }
    return false;
}
// algorithms

void Maze::EnemyMovement() {
    for (auto enemy: enemies) {
        movement move = enemy->moveSmartV2();
        if (move == UP and !enemy->GetCurrentTile()->getUp()->isEnemy()) {
            enemy->getCurrentTile()->setEnemy(false);
            enemy->setCurrentTile(enemy->GetCurrentTile()->getUp());
            enemy->getCurrentTile()->setEnemy(true);
        }else if (move == DOWN and !enemy->GetCurrentTile()->getDown()->isEnemy()) {
            enemy->getCurrentTile()->setEnemy(false);
            enemy->setCurrentTile(enemy->GetCurrentTile()->getDown());
            enemy->getCurrentTile()->setEnemy(true);
        } else if (move == RIGHT and !enemy->GetCurrentTile()->getRight()->isEnemy()) {
            enemy->getCurrentTile()->setEnemy(false);
            enemy->setCurrentTile(enemy->GetCurrentTile()->getRight());
            enemy->getCurrentTile()->setEnemy(true);
        } else if (move == LEFT and !enemy->GetCurrentTile()->getLeft()->isEnemy()) {
            enemy->getCurrentTile()->setEnemy(false);
            enemy->setCurrentTile(enemy->GetCurrentTile()->getLeft());
            enemy->getCurrentTile()->setEnemy(true);
        }
        if(enemy->getCurrentTile() == player->GetCurrentTile()){
            player->playerdied();
        }
    }
}

/*TFA minimize*/
void Maze::recursionMinimize(Maze *&maze, map<set<Path*>, bool> &Table, vector<set<Path*>> &markedStates) {
    int amMarked = markedStates.size();
    for (const auto& koppel : markedStates){
        vector<Path*> vectorMarked;
        vectorMarked.reserve(koppel.size());
        for (auto newKop : koppel){
            vectorMarked.push_back(newKop);
        }
        for (const auto& trans1 : transitions) {
            for (const auto& trans2 : transitions) {
                if (trans1 != trans2){
                    if (trans1.second.first == trans2.second.first and trans1.second.second ==  vectorMarked[0] and trans2.second.second == vectorMarked[1]){
                        addState({trans1.first, trans2.first}, markedStates);
                        Table[{trans1.first, trans2.first}] = false;
                    }
                }
            }
        }
        int newMarked = markedStates.size();
        if (amMarked != newMarked){
            recursionMinimize(maze, Table, markedStates);
        }
    }
}


void Maze::minimize() {
    // Create empty DFA
    DFA* newDFA = new DFA();
    // Create containers
    vector<vector<Node*>> newStates;
    vector<Node*> temp;
    set<Node*> finalV;
    set<Node*> beginV;
    set<transition*> newTransitions;
    newDFA->setAlphabet( { 'w' , 'a' , 's' , 'd' } );
    int count = 0;
    // Convert each tile to a state
    Path *currentPath;
    Path *adjacentTile;
    Node *currentNode;
    transition *newTransition;
    Node *begin;
    Node *end;
    Node *newNode;
    for(int i = 0; i< width; i++){
        for(int j = 0; j< height; j++){
            currentPath = this->at(i).at(j);
            newNode = new Node(to_string(count) , currentPath->isStarting() , currentPath->isAccepting());
            if(newNode->isAccepting()){
                finalV.insert(newNode);
            }
            if(newNode->isStarting()){
                beginV.insert(newNode);
            }
            count++;
            temp.push_back(newNode);
        }
        newStates.push_back(temp);
        temp = {};
    }
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            currentPath = this->at(i).at(j);
            currentNode = newStates.at(i).at(j);
            // Make transition with tile above
            adjacentTile = currentPath->getUp();
            if(adjacentTile != nullptr && adjacentTile->getSettings() == wall){
                begin = currentNode;
                end = newStates[i-1][j];
                newTransition = new transition(begin , end , 'w');
                newTransitions.insert(newTransition);
            }
            else{
                newTransition = new transition(currentNode , currentNode , 'w');
                newTransitions.insert(newTransition);
            }
            // Make transition with tile below
            adjacentTile = currentPath->getDown();
            if(adjacentTile != nullptr && adjacentTile->getSettings() == wall){
                begin = currentNode;
                end = newStates[i+1][j];
                newTransition = new transition(begin , end , 'w');
                newTransitions.insert(newTransition);
            }
            else{
                newTransition = new transition(currentNode , currentNode , 'w');
                newTransitions.insert(newTransition);
            }
            // Make transition with tile left
            adjacentTile = currentPath->getLeft();
            if(adjacentTile != nullptr && adjacentTile->getSettings() == wall){
                begin = currentNode;
                end = newStates[i][j-1];
                newTransition = new transition(begin , end , 'w');
                newTransitions.insert(newTransition);
            }
            else{
                newTransition = new transition(currentNode , currentNode , 'w');
                newTransitions.insert(newTransition);
            }
            // Make transition with tile right
            adjacentTile = currentPath->getRight();
            if(adjacentTile != nullptr && adjacentTile->getSettings() == wall){
                begin = currentNode;
                end = newStates[i][j+1];
                newTransition = new transition(begin , end , 'w');
                newTransitions.insert(newTransition);
            }
            else{
                newTransition = new transition(currentNode , currentNode , 'w');
                newTransitions.insert(newTransition);
            }
        }
    }
    set<Node*> newV;
    for(auto v : newStates){
        for(auto n : v){
            newV.insert(n);
        }
    }
    // Set all the dfa elements
    newDFA->setNodes(newV);
    newDFA->setTransitions(newTransitions);
    newDFA->setBegin(beginV);
    newDFA->setFinal(finalV);
    newDFA->minimize();
    // Save the dfa
    mazeDFA = newDFA;
}

void Maze::addState(const set<Path *>& kopppel, vector<set<Path*>>& markedState) {
    bool init = false;
    for (const auto &Pairs:markedState) {
        if (Pairs == kopppel){
            init = true;
            break;
        }
    }
    if (!init){
        markedState.push_back(kopppel);
    }
}

bool Maze::inItV2(const vector<set<Path*>>& sets, set<Path*> setPath){
    for (const auto& couple : sets){
        set<Path*> intersection;
        set_intersection(couple.begin(), couple.end(), setPath.begin(), setPath.begin(), inserter(intersection, intersection.begin()));
        if (!intersection.empty()){
            return true;
        }
    }
    return false;
}

void Maze::reformat(map<set<Path *>, bool> &Table, Maze *&maze) {
    vector<set<Path*>> equivalentSets;
    // all equivalent states
    for (const auto& couple : Table){
        if (couple.second){
            equivalentSets.push_back(couple.first);
        }
    }
    /*// all non equivalent states
    for (auto state : allPaths){
        if (!inItV2(equivalentSets, state)){
            set<Path*> path;
            path.insert(state);
            equivalentSets.push_back(path);
        }
    }*/
    // combine equivalent states to one set of states
    vector<set<Path*>> newEquiPaths;
    for (const auto& setState1 : equivalentSets){
        for (const auto& setState2 : equivalentSets){
            set<Path*> intersection;
            set_intersection(setState1.begin(), setState1.end(), setState2.begin(), setState2.end(), inserter(intersection, intersection.begin()));
            if (!intersection.empty()){
                set<Path*> Union;
                set_union(setState1.begin(), setState1.end(), setState2.begin(), setState2.end(), inserter(Union, Union.begin()));
                newEquiPaths.push_back(Union);
            }
        }
    }
    for (const auto& setPath : equivalentSets){
        if (!inItV2(newEquiPaths, setPath)){
            newEquiPaths.push_back(setPath);
        }
    }

    for (auto state : allPaths){
        set<Path*> setState = {state};
        if (!inItV2(newEquiPaths, setState)){
            set<Path*> path;
            path.insert(state);
            equivalentSets.push_back(path);
        }
    }

    // combine all equivalent sets to one state
    for (const auto& setState : newEquiPaths){
        if (setState.size() > 1){

        }
        else {

        }
    }
}

/*DFA -> regex*/
bool Maze::yeah(vector<string> alpha, Path* staat){
    bool yeah = true;
    for(auto i:alpha){
        if(staat->getmap()[staat][i] != staat){
            yeah = false;
        }
    }
    return yeah;
}
bool Maze::done(Path* plaats){
    for(auto i:allPaths){
        if(i==plaats && i->isAccepting()){
            return true;
        }
    }
    return false;
}

bool Maze::doublecheck(vector<Path*> vec, Path* str){
    for(auto i:vec){
        if(i == str){
            return true;
        }
    }
    return false;
}
bool Maze::back(Path* end,string alpha,Path* vorige){
    for(auto i:allPaths){
        if(end == i){
            if(vorige->getmap()[end][alpha] == vorige && i->isAccepting()){
                return true;
            }
        }
    }
    return false;
}

void Maze::toRegex(Path* curr, string even,vector<Path*> gonethere){
    string go = findShortestRoute();
    for(int m=0;m<go.size();m++){
        for(int l=0;l<m;l++){
            regex+= go[l];
        }
        if(m != go.size()-1){
            regex += "(";
        }
        for(int i= m;i<go.size();i++){
            string tempo = "";
            regex += "(";
            for(int j=0;j<=i;j++){
                regex +=go[j];
                tempo += go[j];
            }
            for(auto k:tempo){
                if (k == 's') {
                    regex += "w";
                } else if (k == 'w') {
                    regex += "s";
                } else if (k == 'a') {
                    regex += "d";
                } else if (k == 'd') {
                    regex += "a";
                }
            }
            regex += ")*+";
        }
        regex.pop_back();
        regex.pop_back();
        if(m != go.size()-1){
            regex += ")*";
        }
        for(int l=m;l<go.size();l++){
            regex+= go[l];
        }
        regex += "+";
    }
    regex.pop_back();
}

string Maze::toRgex() {
    toRegex(start,"",{});
    return regex;
}

/*Regex -> enfa -> mssc -> dfa*/
void Maze::toDFA() {

}

/*Dijkstra's algorithm*/
string Maze::findShortestRoute() {
    vector<string> allmoves;
    string finalString;
    Path* even = start;
    start = player->GetCurrentTile();
    recursionShortFinder(start, IDLE, finalString, allmoves,{});
    finalString = allmoves[0];
    for (const auto& move : allmoves){
        if (finalString.size() > move.size()){
            finalString = move;
        }
    }
    start = even;
    return finalString;
}

vector<string> Maze::findShortestcoinroute(){
    Path *eind;
    Path* even = new Path;
    *even = *start;
    vector<Path*> keys;
    for(auto i:allPaths){
        if(i->isAccepting()){
            eind = i;
        }
        if(i->isKey()){
            keys.push_back(i);
        }
    }
    eind->setAccepting(false);
    vector<string> strings;
    start = player->getCurrentTile();
    for(auto i:keys){
        vector<string> allmoves;
        string finalString;
        i->setAccepting(true);
        recursionShortFinder(start, IDLE, finalString, allmoves,{});
        finalString = allmoves[0];
        for (const auto& move : allmoves){
            if (finalString.size() > move.size()){
                finalString = move;
            }
        }
        strings.push_back(finalString);
        i->setAccepting(false);
    }
    eind->setAccepting(true);
    start = even;
    return strings;
}

int amountOfPmoves(Path* current){
    int amountOfMovs = 0;
    if (current->getDown() != nullptr){
        amountOfMovs++;
    }
    if (current->getLeft() != nullptr){
        amountOfMovs++;
    }
    if (current->getRight() != nullptr){
        amountOfMovs++;
    }
    if (current->getUp() != nullptr){
        amountOfMovs++;
    }
    return  amountOfMovs;
}

bool inIt(Path* check, vector<Path*> allPaths){
    for (auto path:allPaths) {
        if (path == check){
            return true;
        }
    }
    return false;
}

pair<string, bool> Maze::recursionShortFinder(Path *current, movement previousMove, const string& finalString, vector<string> &allmoves, vector<Path*> seenPath) {
    pair<string, bool> shortestRoute = {"", true};
    string temp = finalString;
    vector<Path*> seen = std::move(seenPath);
    vector<bool> dubbelCheck = {true, true, true, true}; // up down left right
    if (previousMove == IDLE){
        if (current->getDown() != nullptr){
            temp = "s";
            seen.push_back(current);
            if (recursionShortFinder(current->getDown(), UP, temp, allmoves, seen).second){
                temp = recursionShortFinder(current->getDown(), UP, temp, allmoves,seen).first;
            }
            else {
                shortestRoute.second = false;
            }
        }
        if (current->getUp() != nullptr){
            temp = "w";
            seen.push_back(current);
            if (recursionShortFinder(current->getUp(), DOWN, temp, allmoves, seen).second){
                temp = recursionShortFinder(current->getUp(), DOWN, temp, allmoves,seen).first;
            }
            else {
                shortestRoute.second = false;
            }
        }
        if (current->getLeft() != nullptr){
            temp = "a";
            seen.push_back(current);
            if (recursionShortFinder(current->getLeft(), RIGHT, temp, allmoves, seen).second){
                temp = recursionShortFinder(current->getLeft(), RIGHT, temp, allmoves,seen).first;
            }
            else {
                shortestRoute.second = false;
            }
        }
        if (current->getRight() != nullptr){
            temp = "d";
            seen.push_back(current);
            if (recursionShortFinder(current->getRight(), LEFT, temp, allmoves,seen).second){
                temp = recursionShortFinder(current->getRight(), LEFT, temp, allmoves,seen).first;
            }
            else {
                shortestRoute.second = false;
            }
        }
        if (current->getRight() == nullptr and current->getUp() == nullptr and current->getLeft() == nullptr and current->getDown() == nullptr){
            cout << "No path for start" << endl;
            shortestRoute.second = false;
        }
    }
    else {
        int amountOfMoves = amountOfPmoves(current);

        while(amountOfMoves > 1 and shortestRoute.second){
            if (amountOfMoves == 2){
                if (current->getDown() != nullptr and !inIt(current->getDown(), seen)){
                    seen.push_back(current);
                    current = current->getDown();
                    previousMove = UP;
                    temp += "s";
                }
                else if (current->getUp() != nullptr and !inIt(current->getUp(), seen)){
                    seen.push_back(current);
                    current = current->getUp();
                    previousMove = DOWN;
                    temp += "w";
                }
                else if (current->getLeft() != nullptr and !inIt(current->getLeft(), seen)){
                    seen.push_back(current);
                    current = current->getLeft();
                    previousMove = RIGHT;
                    temp += "a";
                }
                else if (current->getRight() != nullptr and !inIt(current->getRight(), seen)){
                    seen.push_back(current);
                    current = current->getRight();
                    previousMove = LEFT;
                    temp += "d";
                }
                else {
                    shortestRoute.second = false;
                }
                if (current->isAccepting()){
                    allmoves.push_back(temp);
                }
            }
            else {
                if (current->getDown() != nullptr and !inIt(current->getDown(), seen) and dubbelCheck[1]){
                    seen.push_back(current);
                    temp += "s";
                    if (recursionShortFinder(current->getDown(), UP, temp, allmoves, seen).second){
                        temp = recursionShortFinder(current->getDown(), UP, temp, allmoves, seen).first;
                        dubbelCheck[1] = false;
                        if (current->getDown()->isAccepting()){
                            allmoves.push_back(temp);
                        }
                    }
                    else {
                        temp.pop_back();
                        dubbelCheck[1] = false;
                    }
                }
                else {
                    dubbelCheck[1] = false;
                }
                if (current->getUp() != nullptr and !inIt(current->getUp(), seen) and dubbelCheck[0]){
                    seen.push_back(current);
                    temp += "w";
                    if (recursionShortFinder(current->getUp(), UP, temp, allmoves, seen).second){
                        temp = recursionShortFinder(current->getUp(), UP, temp, allmoves, seen).first;
                        dubbelCheck[0] = false;
                        if (current->getUp()->isAccepting()){
                            allmoves.push_back(temp);
                        }
                    }
                    else {
                        temp.pop_back();
                        dubbelCheck[0] = false;
                    }
                }
                else {
                    dubbelCheck[0] = false;
                }
                if (current->getLeft() != nullptr and !inIt(current->getLeft(), seen) and dubbelCheck[2]){
                    seen.push_back(current);
                    temp += "a";
                    if (recursionShortFinder(current->getLeft(), UP, temp, allmoves, seen).second){
                        temp = recursionShortFinder(current->getLeft(), UP, temp, allmoves, seen).first;
                        dubbelCheck[2] = false;
                        if (current->getLeft()->isAccepting()){
                            allmoves.push_back(temp);
                        }
                    }
                    else {
                        temp.pop_back();
                        dubbelCheck[2] = false;
                    }
                }
                else {
                    dubbelCheck[2] = false;
                }
                if (current->getRight() != nullptr and !inIt(current->getRight(), seen) and dubbelCheck[3]){
                    seen.push_back(current);
                    temp += "d";
                    if (recursionShortFinder(current->getRight(), UP, temp, allmoves, seen).second){
                        temp = recursionShortFinder(current->getRight(), UP, temp, allmoves, seen).first;
                        dubbelCheck[3] = false;
                        if (current->getRight()->isAccepting()){
                            allmoves.push_back(temp);
                        }
                    }
                    else {
                        temp.pop_back();
                        dubbelCheck[3] = false;
                    }
                }
                else {
                    dubbelCheck[3]= false;
                }
            }
            amountOfMoves = amountOfPmoves(current);
            if (amountOfMoves <= 1 or (!dubbelCheck[0] and !dubbelCheck[1] and !dubbelCheck[2] and !dubbelCheck[3])){
                shortestRoute.second = false;
            }
        }
    }
    shortestRoute.first = temp;
    return shortestRoute;
}

const string &Maze::getSavedFile() const {
    return savedFile;
}

void Maze::setSavedFile(const string &savedFile) {
    Maze::savedFile = savedFile;
}

const string &Maze::getLevelName() const {
    return levelName;
}

void Maze::setLevelName(const string &levelName) {
    Maze::levelName = levelName;
}

int Maze::getKey_count() const {
    return key_count;
}

void Maze::setKey_count(int key_count) {
    Maze::key_count = key_count;
}

Maze::~Maze() {

}


