#include <iostream>
#include "Maze.h"
#include "Enemy.h"

using namespace std;

int main(int argc, char** argv){
    // Maze* newMaze = new Maze("Level1.json");
    // string filename = LEVDIR;
    // filename += LEV1TXT;
    // newMaze->loadGame(filename);
    // newMaze->saveGame();

    // Create QT App
    // QApplication a(argc , argv);
    // MazeGUI_design maze;
    // maze.show();

    // test enemy training
    /*auto* enemy = new Enemy();
    enemy->train("../EnemyTrainer/Training1.txt");
    enemy->train("../EnemyTrainer/Training2.txt");
    for (int i = 0; i < 10; ++i) {
        movement action = enemy->moveSmart();
        if (action == UP){
            cout << "up" << endl;
        }
        else if (action == DOWN){
            cout << "down" << endl;
        }
        else if (action == LEFT){
            cout << "left" << endl;
        }
        else {
            cout << "right" << endl;
        }
    }*/
    auto* maze = new Maze(LEV1JSON);
    string route = maze->findShortestRoute();
    cout << route << endl;

    cout << "Ha you ran this bullshit" << endl;
//    return a.exec();
}