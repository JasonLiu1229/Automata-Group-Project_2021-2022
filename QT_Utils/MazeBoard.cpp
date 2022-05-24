#include "MazeBoard.h"
#include "MazeLayout.h"
#include <qglobal.h>

MazeBoard::MazeBoard() : MazeWindow(nullptr) {
    if(this != nullptr){
    MazeLayout* layout = this->getLayout();
    }
    // Temp
    // Choose layout file
    gameLayout = new Maze("Level1.json");
    string filename = LEVDIR;
    filename += LEV1TXT;
    gameLayout->loadGame(filename);
    gameLayout->saveGame();
    update();
}

void MazeBoard::update() {
    quint32 width = 1080 / gameLayout->getWidth();
    quint32 height = 720 / gameLayout->getHeight();
    this->getLayout()->setTileWidth(width);
    this->getLayout()->setTileHeight(height);
    this->getLayout()->drawBoard(gameLayout);
}

void MazeBoard::newGame() {

}

void MazeBoard::open() {
    // Choose layout file
    gameLayout = new Maze("Level1.json");
    // string filename = LEVDIR;
    // filename += LEV1TXT;
    gameLayout->loadGame(LEV1TXT);
    gameLayout->saveGame();
    update();
}

void MazeBoard::save() {

}


