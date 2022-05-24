#include <iostream>
#include <QApplication>
#include <QPushButton>
#include <QtWidgets/QGraphicsScene>

#include "QT_Utils/MazeBoard.h"
#include "Maze.h"

using namespace std;

int main(int argc, char** argv){
    Maze* newMaze = new Maze("Level1.json");
    string filename = LEVDIR;
    filename += LEV1TXT;
    newMaze->loadGame(filename);
    newMaze->saveGame();
    // Create QT App
    QApplication a(argc , argv);
    MazeBoard maze;
    maze.show();

    cout << "Ha you ran this bullshit" << endl;
    return a.exec();
}