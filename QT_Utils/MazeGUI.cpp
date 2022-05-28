#include "MazeGUI.h"
#include "MazeLayout.h"
#include <qglobal.h>
#include <QInputDialog>
#include <QGroupBox>
#include <QInputEvent>
#include <QRadioButton>
#include <QGridLayout>
#include "../json.hpp"

using json = nlohmann::json;

MazeGUI::MazeGUI() : MazeWindow(nullptr) {
    MazeLayout* layout = this->getLayout();
    // Temp
    // Choose layout file
    string filename = LEVDIR;
    filename += LEV1TXT;
    gameLayout = new Maze(filename);
    //niet nodig
    //gameLayout->loadGame(filename);
    //gameLayout->saveGame();
    update();
}

MazeGUI::MazeGUI(const string& filename) {
    ifstream in("../JSON-Files/"+filename);
    json j;
    in >> j;
    string file = LEVDIR;
    file += j.at("Level").at("fileName");
    gameLayout = new Maze(file);
}

void MazeGUI::update() {
    quint32 width = static_cast<quint32>(1080 / gameLayout->getWidth());
    quint32 height = static_cast<quint32>(700 / gameLayout->getHeight());
    this->getLayout()->setTileWidth(width);
    this->getLayout()->setTileHeight(height);
    this->getLayout()->refreshMaze(gameLayout);
}

void MazeGUI::newGame() {
    // Choose layout file (json)
    ifstream in("../JSON-Files/Level1.json");
    json j;
    in >> j;
    string file = LEVDIR;
    file += j.at("Level").at("fileName");
    gameLayout = new Maze(file);
    update();
}

void MazeGUI::open() {
    /*
    // Choose layout file
    gameLayout = new Maze("Level1.json");
    // string filename = LEVDIR;
    // filename += LEV1TXT;
    gameLayout->loadGame(LEV1TXT);
    //gameLayout->saveGame();
    */
    // Choose layout file (json)
    ifstream in("../JSON-Files/Level1.json");
    json j;
    in >> j;
    string file = LEVDIR;
    file += j.at("Level").at("fileName");
    gameLayout = new Maze(file);
    update();
    // Add corresponding save values
}

void MazeGUI::save() {
    //TBD
}

void MazeGUI::on_actionOptions_triggered() {
//    // Get width
//    int tileWidth = QInputDialog::getInt(this, tr("Options"), tr("TileWidth:"), 25, 0, 100, 1, &ok);
//    if (ok) {
//        // Change width
//        this->getLayout()->setTileWidth(static_cast<unsigned int>(tileWidth));
//    }
//    int tileHeight = QInputDialog::getInt(this, tr("Options"), tr("TileHeight:"), 25, 0, 100, 1, &ok);
//    if (ok) {
//        // Change height
//        this->getLayout()->setTileHeight(static_cast<unsigned int>(tileHeight));
//    }

    bool ok;
    QStringList list = OptionsWidget::getStrings(this, &ok);
    // Refresh maze
    if(ok){
        // Change width
        bool isWInt;
        bool isHInt;
        auto w = list.at(0).toInt(&isWInt);
        auto h = list.at(1).toInt(&isHInt);
        if((isWInt || isHInt) && (w > 0 || h > 0)){
            if(w > 0){
                this->getLayout()->setTileWidth(w);
            }
            if(h > 0){
                this->getLayout()->setTileHeight(h);
            }
            this->getLayout()->refreshMaze(gameLayout);
            // Resize window to remove white spaces
            int newWidth = gameLayout->getWidth() * this->getLayout()->getNTileWidth() * 1.1;
            int newHeight = gameLayout->getHeight() * this->getLayout()->getNTileHeight() * 1.1;
            this->resize(newWidth , newHeight);
            this->setSizeIncrement(newWidth / 10 , newHeight / 10);
        }
    }
}
