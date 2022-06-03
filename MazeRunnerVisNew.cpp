#include <iostream>
#include <QApplication>
#include <QPushButton>
#include <QtWidgets/QGraphicsScene>
#include "QT_UI_Design/ui_MazeWindow.h"
#include "Maze.h"
#include "Enemy.h"
#include "QKeyEvent"

using namespace std;
using namespace Ui;

int main(int argc, char** argv){
    // Create QT App
    QApplication a(argc , argv);


//    // Set up ui im gay
    auto w = new Ui_MazeWindow();
    auto newWindow = new QMainWindow;
    w->setupUi(newWindow);
    newWindow->show();

    return a.exec();
}
