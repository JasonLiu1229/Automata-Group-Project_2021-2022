//
// Created by siebe on 24/05/2022.
//

#ifndef AUTOMATA_GROUP_PROJECT_2021_2022_MAZEWINDOW_H
#define AUTOMATA_GROUP_PROJECT_2021_2022_MAZEWINDOW_H


#include <QMainWindow>
#include <QtUiTools/QtUiTools>

class MazeWindow : public QMainWindow {
public:
    static QWidget *loadUiFile(QWidget *parent);
};


#endif //AUTOMATA_GROUP_PROJECT_2021_2022_MAZEWINDOW_H
