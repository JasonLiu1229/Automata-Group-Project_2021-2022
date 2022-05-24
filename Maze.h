#ifndef AUTOMATA_GROUP_PROJECT_2021_2022_MAZE_H
#define AUTOMATA_GROUP_PROJECT_2021_2022_MAZE_H
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Standard_Values.h"

using namespace std;

class Path;
class Collectable_DFA;

class Maze : vector<vector<Path*>> {
    // Maze specs
    int width;
    int height;
    int key_count;

    // File specs
    string levelName;

    // Collectables dfa
    Collectable_DFA* collectedKeys;

    // UI
    bool customLevel;
    gameStatus status;

public:
    Maze();

    explicit Maze(const string &fileName);

    // level parsing
    bool generateMaze(const string &filename);

    // user interface
    void playMaze();

    void pauseMaze();

    void generateCustom();

    void saveGame();

    void loadGame(const string &fileName);

    // simulate
    void simulateStart();

    virtual ~Maze();
};


#endif //AUTOMATA_GROUP_PROJECT_2021_2022_MAZE_H
