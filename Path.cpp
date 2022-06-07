#include "Path.h"

Path::Path() : up(nullptr), down(nullptr), left(nullptr), right(nullptr), starting(false), accepting(false), settings(path), key(false) , enemy(false){}

Path *Path::getLeft() const {
    return left;
}

void Path::setLeft(Path *left) {
    Path::left = left;
}

Path *Path::getUp() const {
    return up;
}

void Path::setUp(Path *up) {
    Path::up = up;
}

Path *Path::getDown() const {
    return down;
}

void Path::setDown(Path *down) {
    Path::down = down;
}

Path *Path::getRight() const {
    return right;
}

void Path::setRight(Path *right) {
    Path::right = right;
}

bool Path::isStarting() const {
    return starting;
}

void Path::setStarting(bool start) {
    Path::starting = start;
}

bool Path::isAccepting() const {
    return accepting;
}

void Path::setAccepting(bool accepting) {
    Path::accepting = accepting;
}


tileSettings Path::getSettings() const {
    return settings;
}

void Path::setSettings(tileSettings new_settings) {
    Path::settings = new_settings;
}

bool Path::isKey() const {
    return key;
}

void Path::setKey(bool key) {
    Path::key = key;
}

void Path::setpath(string input, Path* next){
    directions[this][input] = next;
}

void Path::setmovement(string input){
    movement.push_back(input);
}

vector<string> Path::getalphabet(){
    return movement;
}

Path* Path::getpath(){
    return this;
}

map<Path*,map<string,Path*>> Path::getmap(){
    return directions;
}

Path::~Path() {}

bool Path::isWall() {
    return settings == wall;
}

bool Path::isEnemy(){
    return enemy;
}

void Path::setEnemy(bool enem) {
    enemy = enem;
}

bool Path::isEnemy(){
    return enemy;
}

void Path::setEnemy(bool enem) {
    enemy = enem;
}
