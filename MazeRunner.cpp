#include <iostream>
#include <QApplication>
#include <QPushButton>
#include <QtWidgets/QGraphicsScene>

#include "QT_Utils/MazeBoard.h"
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
    /*QApplication a(argc , argv);
    MazeBoard maze;
    maze.show();*/

    /*// test enemy training
    auto* enemy = new Enemy();
    enemy->train("../EnemyTrainer/Trainig1.txt");
    for (int i = 0; i < 10; ++i) {
        movement action = enemy->move();
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

    cout << "Ha you ran this bullshit" << endl;
    /*return a.exec();*/
}