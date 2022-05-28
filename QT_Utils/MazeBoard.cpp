#include "MazeBoard.h"
#include <QtWidgets>
#include <QPixmap>
#include <qnamespace.h>
#include "../Maze.h"
#include "../Path.h"

const QVariant kTile=555;
const QVariant kPiece=777;
const quint32 kWidth=45;

MazeBoard::MazeBoard(QObject *parent) : QGraphicsScene(parent) {
    nTileWidth = kWidth;
    nTileHeight = kWidth;
    nBorderWidth = 0;
    nBorderHeight = 0;
    wallColor = Qt::black;
    pathColor = Qt::gray;
    doorColor = QColor(150,75,0);
    playerColor = Qt::white;
    enemyColor = QColor(138,3,3);
}

void MazeBoard::drawTile(int i, int j , tileSettings &tileType)
{
    QGraphicsRectItem *tile = new QGraphicsRectItem( j * nTileWidth , i * nTileHeight , nTileWidth , nTileHeight );
    
    if( tileType == wall ) {
        // If the cell has no focus, it also has no danger indication
        tile->setBrush(QBrush(wallColor, Qt::SolidPattern));
    }
    else{
        // If the cell has no focus, it also has no danger indication
        tile->setBrush(QBrush(pathColor, Qt::SolidPattern));
    }
    tile->setCacheMode(QGraphicsItem::NoCache);
    tile->setData(0, kTile );
    addItem(tile);
}

void MazeBoard::drawPlayer(int x, int y){
    QGraphicsRectItem *tile = new QGraphicsRectItem( x * nTileWidth , y * nTileHeight , nTileWidth , nTileHeight );
    tile->setBrush(QBrush(playerColor , Qt::SolidPattern));
    tile->setCacheMode(QGraphicsItem::NoCache);
    tile->setData(0, kTile );
    addItem(tile);
}

void MazeBoard::drawMaze(Maze *&layout)
{
    Path* currentTile;
    tileSettings setting;
    for(int i=0; i<layout->getWidth(); i++)
    {
        for(int j=0; j<layout->getHeight(); j++)
        {
            currentTile = layout->getPath(i,j);
            setting = currentTile->getSettings();
            if(currentTile->isStarting()){
                drawPlayer(i , j);
            }
            else{
                drawTile(i,j,setting);
            }
        }
    }
}

void MazeBoard::refreshMaze(Maze *&layout) {
    Path* currentTile;
    tileSettings setting;
    qDeleteAll(items());
    drawMaze(layout);
}

void MazeBoard::refreshTile(int i, int j, tileSettings &tileType) {
    int x = xFromCol(j);
    int y = yFromRow(i);
    QGraphicsItem *currentItem = itemAt( x , y, QTransform() );
    while (currentItem) {
        delete currentItem;
        currentItem = itemAt( x , y , QTransform() );
    }
    drawTile(i,j,tileType);
}

void MazeBoard::refreshPlayer(int x, int y) {
    QGraphicsItem *currentItem = itemAt( xFromCol(y) , yFromRow(x), QTransform() );
    while (currentItem) {
        delete currentItem;
        currentItem = itemAt( xFromCol(y) , yFromRow(x) , QTransform() );
    }
    drawPlayer(x,y);
}

void MazeBoard::setTileWidth(unsigned int newWidth){
    nTileWidth = newWidth;
}

void MazeBoard::setBorderWidth(unsigned int newWidth){
    nBorderWidth = newWidth;
}

void MazeBoard::setTileHeight(unsigned int newHeight){
    nTileHeight = newHeight;
}

void MazeBoard::setBorderHeight(unsigned int newHeight){
    nBorderHeight = newHeight;
}

quint32 MazeBoard::getNTileWidth() const {
    return nTileWidth;
}

quint32 MazeBoard::getNTileHeight() const {
    return nTileHeight;
}

quint32 MazeBoard::getNBorderWidth() const {
    return nBorderWidth;
}

quint32 MazeBoard::getNBorderHeight() const {
    return nBorderHeight;
}

void MazeBoard::resize(int w , int h) {

}

MazeBoard::~MazeBoard() {

}

void MazeBoard::keyPressEvent(QKeyEvent *keyEvent) {
    pressedKey = keyEvent->key();
    emit(keyPressed(pressedKey));
    QGraphicsScene::keyPressEvent(keyEvent);
}

const char &MazeBoard::getPressedKey() const {
    return pressedKey;
}
