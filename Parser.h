#ifndef AUTOMATA_GROUP_PROJECT_2021_2022_PARSER_H
#define AUTOMATA_GROUP_PROJECT_2021_2022_PARSER_H
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "json.hpp"
#include "Maze.h"

using json = nlohmann::json;
using namespace std;

class Parser {
    string fileName;
public:
    explicit Parser(string fileName);
};


#endif //AUTOMATA_GROUP_PROJECT_2021_2022_PARSER_H
