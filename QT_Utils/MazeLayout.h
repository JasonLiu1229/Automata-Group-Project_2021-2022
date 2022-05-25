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

    void drawMaze(Maze *&layout);

    void refreshMaze(Maze *&layout);

    void setTileWidth(unsigned int newWidth);

    quint32 getNTileWidth() const;

    void setTileHeight(unsigned int newHeight);

    quint32 getNTileHeight() const;

    void setBorderWidth(unsigned int newWidth);

    quint32 getNBorderWidth() const;

    void setBorderHeight(unsigned int newHeight);

    quint32 getNBorderHeight() const;

    void resize(int w , int h);

signals:
   void clicked(int x,int y);

private:
    void drawTile(int i, int j , tileSettings &tileType);

    void drawPlayer(int x , int y);

    void refreshTile(int i , int j , tileSettings &tileType);

    void refreshPlayer(int x , int y);


    quint8 rowFromPoint(int y) const { return static_cast<quint8>(y / nTileWidth); }
    quint8 colFromPoint(int x) const { return static_cast<quint8>(x / nTileHeight); }

    quint32 xFromCol(int c) const { return static_cast<quint32>(c * nTileWidth + 0.5 * nTileWidth); }
    quint32 yFromRow(int r) const { return static_cast<quint32>(r * nTileHeight + 0.5 * nTileHeight); }

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
