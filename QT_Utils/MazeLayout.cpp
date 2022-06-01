#include "MazeLayout.h"
#include <QtWidgets>
#include <QPixmap>
#include <qnamespace.h>
#include "../Maze.h"
#include "../Path.h"

const QVariant kTile=555;
const QVariant kPiece=777;
const quint32 kWidth=45;

MazeLayout::MazeLayout(QObject *parent) : QGraphicsScene(parent) {
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

void MazeLayout::drawTile(int i, int j , tileSettings &tileType)
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

void MazeLayout::drawPlayer(int x, int y){
    QGraphicsRectItem *tile = new QGraphicsRectItem( x * nTileWidth , y * nTileHeight , nTileWidth , nTileHeight );
    tile->setBrush(QBrush(playerColor , Qt::SolidPattern));
    tile->setCacheMode(QGraphicsItem::NoCache);
    tile->setData(0, kTile );
    addItem(tile);
}

void MazeLayout::drawMaze(Maze *&layout)
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

void MazeLayout::refreshMaze(Maze *&layout) {
    qDeleteAll(items());
    drawMaze(layout);
}

void MazeLayout::refreshTile(int i, int j, tileSettings &tileType) {
    int x = xFromCol(j);
    int y = yFromRow(i);
    QGraphicsItem *currentItem = itemAt( x , y, QTransform() );
    while (currentItem) {
        delete currentItem;
        currentItem = itemAt( x , y , QTransform() );
    }
    drawTile(i,j,tileType);
}

void MazeLayout::refreshPlayer(int x, int y) {
    QGraphicsItem *currentItem = itemAt( xFromCol(y) , yFromRow(x), QTransform() );
    while (currentItem) {
        delete currentItem;
        currentItem = itemAt( xFromCol(y) , yFromRow(x) , QTransform() );
    }
    drawPlayer(x,y);
}

void MazeLayout::setTileWidth(unsigned int newWidth){
    nTileWidth = newWidth;
}

void MazeLayout::setBorderWidth(unsigned int newWidth){
    nBorderWidth = newWidth;
}

void MazeLayout::setTileHeight(unsigned int newHeight){
    nTileHeight = newHeight;
}

void MazeLayout::setBorderHeight(unsigned int newHeight){
    nBorderHeight = newHeight;
}

quint32 MazeLayout::getNTileWidth() const {
    return nTileWidth;
}

quint32 MazeLayout::getNTileHeight() const {
    return nTileHeight;
}

quint32 MazeLayout::getNBorderWidth() const {
    return nBorderWidth;
}

quint32 MazeLayout::getNBorderHeight() const {
    return nBorderHeight;
}

void MazeLayout::resize(int w , int h) {

}

MazeLayout::~MazeLayout() {

}

void MazeLayout::keyPressEvent(QKeyEvent *keyEvent) {
    pressedKey = keyEvent->key();
    emit(keyPressed(pressedKey));
    QGraphicsScene::keyPressEvent(keyEvent);
}

const char &MazeLayout::getPressedKey() const {
    return pressedKey;
}
