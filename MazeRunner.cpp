#include <iostream>
#include "Maze.h"

using namespace std;

int main(int argc, char** argv){
    Maze* newMaze = new Maze("Level1.json");
    newMaze->loadGame("../TXT-Files/Level1.txt");
    cout << "Ha you ran this bullshit" << endl;
}