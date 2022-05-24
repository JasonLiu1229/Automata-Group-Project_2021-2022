//
// Created by student on 24.05.22.
//

#ifndef AUTOMATA_GROUP_PROJECT_2021_2022_MAZEBOARD_H
#define AUTOMATA_GROUP_PROJECT_2021_2022_MAZEBOARD_H

#include "MazeWindow.h"
#include "../Maze.h"

class MazeBoard : public MazeWindow {
public:
    MazeBoard();

    void update();

private:
    Maze game;

    void newGame() override;
    void open() override;
    void save() override;
};


#endif //AUTOMATA_GROUP_PROJECT_2021_2022_MAZEBOARD_H
