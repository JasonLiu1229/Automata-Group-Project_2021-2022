#ifndef AUTOMATA_GROUP_PROJECT_2021_2022_MAZE_H
#define AUTOMATA_GROUP_PROJECT_2021_2022_MAZE_H
#include <vector>
#include <string>

using namespace std;

class Path;

class Maze : vector<vector<Path*>> {
    int width;
    int height;
    string levelName;
public:
    Maze();

    Maze(int width, int height);
};


#endif //AUTOMATA_GROUP_PROJECT_2021_2022_MAZE_H
