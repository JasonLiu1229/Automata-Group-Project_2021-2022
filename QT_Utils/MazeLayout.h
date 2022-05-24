#ifndef AUTOMATA_GROUP_PROJECT_2021_2022_MAZELAYOUT_H
#define AUTOMATA_GROUP_PROJECT_2021_2022_MAZELAYOUT_H


#include <QtWidgets/QGraphicsScene>

class QAction;
class QActionGroup;

class MazeLayout : public QGraphicsScene {

Q_OBJECT

public:
    explicit MazeLayout(QObject *parent = 0);

    virtual ~MazeLayout();

signals:
   void clicked(int x,int y);

private:
    void drawTile(int i, int j);

    void drawBoard();


//    quint8 rowFromPoint(int y) const { return y / nPieceWidth; }
//    quint8 colFromPoint(int x) const { return x / nPieceWidth; }

//    quint32 xFromCol(int c) const { return c*nPieceWidth + 0.5*nPieceWidth; }
//    quint32 yFromRow(int r) const { return r*nPieceWidth + 0.5*nPieceWidth; }

    QColor wallColor;
    QColor pathColor;
    QColor doorColor;
    QColor playerColor;
    QColor enemyColor;

    quint32 nPieceWidth;
    quint32 nBorderWidth;

    // qint8 focusRow, focusCol;
};


#endif //AUTOMATA_GROUP_PROJECT_2021_2022_MAZELAYOUT_H
