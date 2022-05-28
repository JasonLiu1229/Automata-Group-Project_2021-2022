#ifndef AUTOMATA_GROUP_PROJECT_2021_2022_MAZEGUI_H
#define AUTOMATA_GROUP_PROJECT_2021_2022_MAZEGUI_H

#include "MazeWindow.h"
#include "../Maze.h"

class MazeGUI : public MazeWindow {
public:
    MazeGUI();
    MazeGUI(const string& filename);

    void update() override;

private:
    Maze* gameLayout;

    void newGame() override;
    void open() override;
    void save() override;
    void on_actionOptions_triggered() override;
};


#endif //AUTOMATA_GROUP_PROJECT_2021_2022_MAZEGUI_H
