#ifndef AUTOMATA_GROUP_PROJECT_2021_2022_MAZE_H
#define AUTOMATA_GROUP_PROJECT_2021_2022_MAZE_H
#include <vector>
#include <map>
#include <set>
#include <string>
#include <iostream>
#include <fstream>
#include "Player.h"
#include "Collectable_DFA.h"
#include "miniState.h"
#include "Standard_Values.h"

using namespace std;

class Path;
class Collectable_DFA;

class Maze : vector<vector<Path*>> {
    // Maze specs
    int width;
    int height;
    int key_count;

    // few variable for regex
    map<pair<Path*,string>,int> indexpositie;
    int indexen;
    string regex;
    Path* curren;
    string even2;
    bool zijner;

    // File specs
    string levelName;

    // Collectables dfa
    Collectable_DFA* collectedKeys;

    // UI
    bool customLevel;
    gameStatus status;

    //speler
    Player* player;

    // all Paths
    vector<Path*> allPaths;
    Path* start;

public:
    // constructors
    Maze();

    explicit Maze(const string &fileName);

    // level parsing
    bool generateMaze(const string &filename);

    // Getters and setters
    int getWidth() const;

    int getHeight() const;

    Path* getPath(int i , int j);

    // user interface
    void playMaze();

    void pauseMaze();

    void generateCustom();

    void saveGame();

    void loadGame(const string &fileName);

    // simulate
    void simulateStart();

    //DFA -> Regex
    void toRegex(Path* curr, string even,vector<Path*> gonethere); // DFA to REGEX

    bool done(Path* plaats); // to see if we are at an end state

    bool yeah(vector<string> alpha, Path* staat); //to check if we are not going to a deadend

    bool doublecheck(vector<Path*> vec, Path* str); //Checking if we went there or not

    bool back(Path* end,string alpha,Path* vorige); //if it loops on itself

    // algorithms
    Maze* minimize();   // TFA

    string toRgex();    // DFA -> regex

    void toDFA();       // regex -> enfa -> mssc -> dfa

    // destructor
    virtual ~Maze();
};


#endif //AUTOMATA_GROUP_PROJECT_2021_2022_MAZE_H
