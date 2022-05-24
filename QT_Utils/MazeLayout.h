#ifndef AUTOMATA_GROUP_PROJECT_2021_2022_MAZELAYOUT_H
#define AUTOMATA_GROUP_PROJECT_2021_2022_MAZELAYOUT_H


#include <QtWidgets/QGraphicsScene>
#include <qglobal.h>
#include "../Standard_Values.h"
class QAction;
class QActionGroup;
class Maze;
class MazeLayout : public QGraphicsScene {

Q_OBJECT

public:
    explicit MazeLayout(QObject *parent = 0);

    virtual ~MazeLayout();

    void drawBoard(Maze* &layout);

    void setTileWidth(unsigned int newWidth);

    void setTileHeight(unsigned int newHeight);

    void setBorderWidth(unsigned int newWidth);

    void setBorderHeight(unsigned int newHeight);

signals:
   void clicked(int x,int y);

private:
    void drawTile(int i, int j , tileSettings &tileType);

    void drawPlayer(int x , int y);



//    quint8 rowFromPoint(int y) const { return y / nPieceWidth; }
//    quint8 colFromPoint(int x) const { return x / nPieceWidth; }

//    quint32 xFromCol(int c) const { return c*nPieceWidth + 0.5*nPieceWidth; }
//    quint32 yFromRow(int r) const { return r*nPieceWidth + 0.5*nPieceWidth; }

    QColor wallColor;
    QColor pathColor;
    QColor doorColor;
    QColor playerColor;
    QColor enemyColor;

    quint32 nTileWidth;
    quint32 nTileHeight;
    quint32 nBorderWidth;
    quint32 nBorderHeight;

    // qint8 focusRow, focusCol;
};


#endif //AUTOMATA_GROUP_PROJECT_2021_2022_MAZELAYOUT_H
