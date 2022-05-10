
#ifndef AUTOMATA_GROUP_PROJECT_2021_2022_KEY_H
#define AUTOMATA_GROUP_PROJECT_2021_2022_KEY_H
#include "Path.h"

class Key : public Path{
    bool collected;
public:
    Key();

    bool isCollected() const;

    void setCollected(bool collected);

    virtual ~Key();
};


#endif //AUTOMATA_GROUP_PROJECT_2021_2022_KEY_H
