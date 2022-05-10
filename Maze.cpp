#include "Maze.h"
#include "Path.h"

Maze::Maze(){}

Maze::Maze(int width, int height) : width(width), height(height) {
    for (int i = 0; i < width; ++i) {
        vector<Path*> wholePath;
        for (int j = 0; j < height; ++j) {
            Path* newPath = new Path();
            wholePath.push_back(newPath);
        }
        this->push_back(wholePath);
    }
}
