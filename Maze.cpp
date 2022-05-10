#include "Maze.h"

#include <utility>
#include "Path.h"

Maze::Maze(){}

Maze::Maze(string  fileName, int width, int height) : width(width), height(height), levelName(std::move(fileName)) {
    for (int i = 0; i < width; ++i) {
        vector<Path*> wholePath;
        for (int j = 0; j < height; ++j) {
            Path* newPath = new Path();
            wholePath.push_back(newPath);
        }
        this->push_back(wholePath);
    }
}

Maze::~Maze() {

}
