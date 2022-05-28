#include <iostream>
#include <QApplication>
#include <QPushButton>
#include <QtWidgets/QGraphicsScene>
#include "QT_Utils/MazeGUI.h"
#include "Maze.h"
#include "Enemy.h"
#include "QKeyEvent"

using namespace std;

int main(int argc, char** argv){
    // Create QT App
    QApplication a(argc , argv);
    MazeGUI maze("Level1.json");
    maze.show();

    cout << "Ha you ran this bullshit" << endl;
    
    return a.exec();
}