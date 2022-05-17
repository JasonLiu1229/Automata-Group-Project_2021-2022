#include <iostream>
#include <QApplication>
#include <QPushButton>
#include "Maze.h"

using namespace std;

int main(int argc, char** argv){
    Maze* newMaze = new Maze("Level1.json");
    string filename = LVLDIR;
    filename += LEV1TXT;
    newMaze->loadGame(filename);
    newMaze->saveGame();
    cout << "Ha you ran this bullshit" << endl;
}