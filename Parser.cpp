

#include "Parser.h"

#include <utility>

Parser::Parser(string fileName) : fileName(fileName) {
    ifstream input(fileName);
    json j;
    input >> j;
    auto level = j["Level"];
    Parser::txt_filename = level["fileName"];
    Parser::regex = level["regex"];
}

string Parser::getTxt_Filename(){
    return Parser::txt_filename;
}