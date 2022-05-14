// custom libs
#include "Maze.h"
#include "Path.h"

// c++ libs
#include <utility>
#include <fstream>

using namespace std;

Maze::Maze(const string &fileName) :levelName(fileName), status(play) {
    bool failed = generateMaze(fileName);

    if (failed){
        cout << "File was corrupted or not found" << endl;
    }
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
}

void Maze::loadGame(const string &fileName) {
    // load status of whole game from txt file
}

Maze::~Maze() {

}
