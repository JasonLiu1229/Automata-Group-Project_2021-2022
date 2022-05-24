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

void MazeLayout::drawBoard(Maze* &layout)
{
    Path* currentTile;
    tileSettings setting;
    for(int i=0; i<layout->getWidth(); i++)
    {
        for(int j=0; j<layout->getHeight(); j++)
        {
            currentTile = layout->getPath(i,j);
            setting = currentTile->getSettings();
            drawTile(i,j,setting);
        }
    }
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

MazeLayout::~MazeLayout() {

}
