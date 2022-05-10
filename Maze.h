#ifndef AUTOMATA_GROUP_PROJECT_2021_2022_MAZE_H
#define AUTOMATA_GROUP_PROJECT_2021_2022_MAZE_H
#include <vector>
#include <string>

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
public:
    Maze();

    Maze(string  fileName, int width, int height);
};


#endif //AUTOMATA_GROUP_PROJECT_2021_2022_MAZE_H
