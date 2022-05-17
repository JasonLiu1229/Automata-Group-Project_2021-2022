

#include "Parser.h"

#include <utility>

Parser::Parser(string fileName) : fileName(std::move(fileName)) {
    ifstream input(fileName);
    json j;
    input >> j;
    Maze* maze = new Maze(); // Give it to the QT-class
    maze->loadGame(j["fileName"]);
}
