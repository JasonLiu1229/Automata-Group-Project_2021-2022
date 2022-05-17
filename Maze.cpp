// custom libs
#include "Maze.h"
#include "Path.h"

// c++ libs
#include <utility>
#include <fstream>

using namespace std;

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
    fstream saveFile;
    FILE* codefile;

    // create file
    bool exists = false;
    int i = 0;
    string filename;
    filename = SVG;
    filename += ".txt";
    while (!exists){
        i++;
        codefile = fopen(filename.c_str(), "r");
        if (codefile){
            filename = SVG;
            filename += '(' + to_string(i) + ')' + ".txt";
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

}

void Maze::simulateStart() {

}

Maze::~Maze() {

}
