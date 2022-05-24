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
    bool failed = generateMaze(fileName);

    if (failed){
        cout << "File was corrupted or not found" << endl;
    }

    simulateStart();
}

Maze::Maze(){}

// read level
bool Maze::generateMaze(const string &filename) {
    /*for (int i = 0; i < width; ++i) {
        vector<Path*> wholePath;
        for (int j = 0; j < height; ++j) {
            Path* newPath = new Path();
            wholePath.push_back(newPath);
        }
        this->push_back(wholePath);
    }*/
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
    ifstream gamefile (fileName);
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

}

Maze::~Maze() {

}
