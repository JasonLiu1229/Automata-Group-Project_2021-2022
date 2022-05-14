#ifndef AUTOMATA_GROUP_PROJECT_2021_2022_MAZE_H
#define AUTOMATA_GROUP_PROJECT_2021_2022_MAZE_H
#include <vector>
#include <string>

#include "Standard_Values.h"
using namespace std;

class Path;

class Maze : vector<vector<Path*>> {
    // Maze specs
    int width;
    int height;

    // File specs
    string levelName;

    // Collectables dfa

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

    virtual ~Maze();
};


#endif //AUTOMATA_GROUP_PROJECT_2021_2022_MAZE_H
