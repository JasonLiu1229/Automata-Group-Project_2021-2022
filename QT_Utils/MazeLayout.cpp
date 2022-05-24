//
// Created by student on 24.05.22.
//

#include "MazeLayout.h"
#include <QtWidgets>
#include <QPixmap>

const QVariant kTile=555;
//const QVariant kPiece=777;
//const quint32 kWidth=45;

MazeLayout::MazeLayout(QObject *parent) : QGraphicsScene(parent) {

    wallColor = Qt::black;
    pathColor = Qt::gray;
    doorColor = QColor(150,75,0);
    playerColor = Qt::white;
    enemyColor = QColor(138,3,3);
    drawBoard();

}

void MazeLayout::drawTile(int i, int j)
{
    QGraphicsRectItem *tile = new QGraphicsRectItem( j * nPieceWidth , i * nPieceWidth , nPieceWidth , nPieceWidth );

    if( i % 2 == j % 2 ) {
        // If the cell has no focus, it also has no danger indication
        tile->setBrush(QBrush(wallColor, Qt::SolidPattern));
    }
    else {
        // If the cell has no focus, it also has no danger indication
        tile->setBrush(QBrush(pathColor, Qt::SolidPattern));
        }

    tile->setCacheMode(QGraphicsItem::NoCache);
    tile->setData(0, kTile );
    addItem(tile);
}



void MazeLayout::drawBoard()
{
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            drawTile(i,j);
        }
    }
}

MazeLayout::~MazeLayout() {

}
