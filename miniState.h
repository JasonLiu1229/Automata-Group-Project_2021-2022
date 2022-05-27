//
// Created by liuja on 17/05/2022.
//

#ifndef AUTOMATA_GROUP_PROJECT_2021_2022_MINISTATE_H
#define AUTOMATA_GROUP_PROJECT_2021_2022_MINISTATE_H


class miniState {
public:
    miniState();

    virtual ~miniState();

    miniState *getNext() const;

    void setNext(miniState *next);

    void setallcollected(bool done);

    bool getkeystate();

private:
    miniState* next;
    bool allCollected;

};


#endif //AUTOMATA_GROUP_PROJECT_2021_2022_MINISTATE_H
