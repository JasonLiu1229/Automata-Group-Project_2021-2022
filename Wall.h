//
// Created by jason on 10/05/2022.
//

#ifndef AUTOMATA_GROUP_PROJECT_2021_2022_WALL_H
#define AUTOMATA_GROUP_PROJECT_2021_2022_WALL_H

#include "Path.h"

class Wall : public Path{
    bool easterEgg;
public:
    Wall();

    explicit Wall(bool easterEgg);

    virtual ~Wall();
};


#endif //AUTOMATA_GROUP_PROJECT_2021_2022_WALL_H
