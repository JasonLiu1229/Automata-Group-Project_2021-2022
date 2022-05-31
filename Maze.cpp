// custom libs
#include "Maze.h"
#include "Path.h"
#include "json.hpp"

// c++ libs
#include <utility>
#include <fstream>
#include <iomanip>

using namespace std;
using json = nlohmann::json;

Maze::Maze(const string &fileName) :levelName(fileName), status(play) , key_count(0) {
    // json file parsing
    ifstream parser;

    parser.open(fileName);

    if (parser.fail()){
        cout << "Error while openning file" << endl;
    }

    if (parser.is_open()){
        json fileJson;

        parser >> fileJson;

        levelName = fileJson["fileName"];

        bool failed = generateMaze(levelName);

        if (!failed){
            cout << "File was corrupted or not found" << endl;
        }
        /*simulateStart();*/
    }

    parser.close();
}

Maze::Maze(): key_count(0){
}

// read level
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
                if(i == '#'){
                    path->setSettings(wall);
                }
                else if(i=='$'){
                    path->setStarting(true);
                    player = new Player(path, "Hendrick");
                }
                else if(i=='&'){
                    path->setAccepting(true);
                }
                else if(i == '^'){
                    path->setKey(true);
                    key_count++;
                }
                pathRow.push_back(path);
            }
            this->push_back(pathRow);
        }
        height = this->size();
        width = this[0].size();

        // set transitions
        return true;
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

void Maze::saveGame() {
    // write status of whole game in a txt file
    // TXT file
    fstream saveFile;
    FILE* codefile;

    // create file
    bool exists = false;
    int i = 0;
    string filename;
    filename = SVG1;
    filename += TXT;

    while (!exists){
        i++;
        codefile = fopen(filename.c_str(), "r");
        if (codefile){
            filename = SVG1;
            filename += '(' + to_string(i) + ')' + TXT;
        }
        else {
            saveFile.open(filename.c_str(), ios::app | ios::ate);
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
    filenameJ = SVG1;
    filenameJ += JSON;

    i = 0;
    while (!exists){
        i++;
        codefile = fopen(filenameJ.c_str(), "r");
        if (codefile){
            filenameJ = SVG1;
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

void Maze::loadGame(const string &fileName) {
    string line;
    ifstream gamefile(fileName);
    if(gamefile.is_open()){
        while(getline(gamefile,line)){
            vector<Path*> weg;
            for(auto i:line){
                Path* road = new Path();
                if(i == '#'){
                    road->setSettings(wall);
                }
                else if(i=='$'){
                    road->setStarting(true);
                    player = new Player(road, "Hendrick");
                }
                else if(i=='&'){
                    road->setAccepting(true);
                }
                else if(i == '^'){
                    road->setKey(true);
                    key_count++;
                }
                weg.push_back(road);
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
            }
            else{
                nextTile = this->at(i-1)[j];
                currentTile->setUp(nextTile);
            }
            // Get tile left
            if(j == 0){
                currentTile->setLeft(nullptr);
            }
            else{
                nextTile = this->at(i)[j-1];
                currentTile->setLeft(nextTile);
            }
            // Get tile right
            if(j == width - 1){
                currentTile->setRight(nullptr);
            }
            else{
                nextTile = this->at(i)[j+1];
                currentTile->setRight(nextTile);
            }
            // Get tile under
            if(i == height - 1){
                currentTile->setDown(nullptr);
            }
            else{
                nextTile = this->at(i+1)[j];
                currentTile->setDown(nextTile);
            }
        }
    }
    

}

void Maze::simulateStart() {
    loadGame(levelName);
    Collectable_DFA keys(key_count);
    /*
    while (!player->GetCurrentTile()->isAccepting() && !keys.getCurrentState()->getkeystate()){
        string movement;
        cin>> movement;
        if(movement == "w"){
            player->GetCurrentTile()->setStarting(false);
            player->SetCurrentTile(player->GetCurrentTile()->getUp());
            player->GetCurrentTile()->setStarting(true);
        }
        else if(movement == "s"){
            player->GetCurrentTile()->setStarting(false);
            player->SetCurrentTile(player->GetCurrentTile()->getDown());
            player->GetCurrentTile()->setStarting(true);
        }
        else if(movement == "a"){
            player->GetCurrentTile()->setStarting(false);
            player->SetCurrentTile(player->GetCurrentTile()->getLeft());
            player->GetCurrentTile()->setStarting(true);
        }
        else if(movement == "d"){
            player->GetCurrentTile()->setStarting(false);
            player->SetCurrentTile(player->GetCurrentTile()->getRight());
            player->GetCurrentTile()->setStarting(true);
        }
        if(player->GetCurrentTile()->isKey()){
            keys.setCurrentState(keys.getCurrentState()->getNext());
        }
    }
    */
}

// algorithms

Maze *Maze::minimize() {
    auto* minimizeMaze = new Maze();
    map<pair<Path*, Path*>, bool> Table;




    return minimizeMaze;
}

string Maze::toRgex() {
    string regex;
    return regex;
}

void Maze::toDFA() {

}

Maze::~Maze() {

}
