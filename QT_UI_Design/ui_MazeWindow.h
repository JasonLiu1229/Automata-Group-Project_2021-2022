/********************************************************************************
** Form generated from reading UI file 'UI_MazeWindowRI4129.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAZEWINDOWRI4129_H
#define UI_MAZEWINDOWRI4129_H

// QT Sources
#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QHeaderView>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QStackedWidget>
#include <QMessageBox>
#include <QCloseEvent>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <qmainwindow.h>

// Custom sources
#include "../Maze.h"


QT_BEGIN_NAMESPACE

class Ui_MazeWindow : public  QMainWindow
{

    Q_OBJECT

public:

    void setupUi(QMainWindow *MainWindow);
    void retranslateUi(QMainWindow *MainWindow);

    void newGame();
    void open();
    void load();
    void save();
    void options();
    void mainMenuReturn();
    void pauseGame();
    void showControls();
    void showHelp();
    void loadLevel(string filename);

private slots:

    void slot_new() {newGame();}
    void slot_open() {open();}
    void slot_save() {save();}
    void slot_load() {load();}
    void slot_options() {options();}
    void slot_mainMenu() {mainMenuReturn();}
    void slot_pauseGame(){pauseGame();}
    void slot_showControls() {showControls();}
    void slot_showHelp() {showHelp();}
    void slot_fullScreen() {
        if (isMaximized()) {
            showNormal();
        } else {
            showMaximized();
        }
    };
    void slot_level1() {loadLevel(LEV1JSON);}
    void slot_level2() {loadLevel(LEV2JSON);}
    void slot_level3() {loadLevel(LEV3JSON);}
    void slot_level4() {loadLevel(LEV4JSON);}

    void on_actionOptions_triggered();
    void on_actionExit_triggered();

    void closeEvent (QCloseEvent *event) override {
        on_actionExit_triggered();
        event->ignore();
    }

private:

    Maze* gameLayout;

    void createActions(QMainWindow *MainWindow);
    void createMenus(QMainWindow *MainWindow);
    void createSelectionScreen(QMainWindow *MainWindow);
    void createLevelScreen(QMainWindow *MainWindow);
    void drawMaze(Maze *&layout);
    void drawTile(int i, int j , tileSettings &tileType);
    void drawPlayer(int x , int y);
    void refreshTile(int i , int j , tileSettings &tileType);
    void refreshPlayer(int x , int y);

    // Main Widgets
    QStackedWidget *MenuScreens;
    QWidget *MainScreen;
    QWidget *LevelSelectionScreen;
    QWidget *levelScreen;
    
    // Menu bar
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuOptions;

    // Status bar
    QStatusBar *statusbar;

    // Main screen
    QWidget *verticalLayoutWidget;
    QVBoxLayout *MainScreenLayout;
    QPushButton *newGameButton;
    QPushButton *LoadGameButton;
    QPushButton *OptionsButton;
    QPushButton *ExitButton;

    // Level selection screen
    QGridLayout *LevelsGrid;
    QPushButton *Level3;
    QPushButton *Level4;
    QPushButton *Level1;
    QPushButton *Level2;
    QPushButton *MenuButton;

    // Level screen
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *mainMenuButton;
    QPushButton *pauseButton;
    QPushButton *HTP_button;
    QPushButton *helpButton;
    QGraphicsView *MazeView;
    QGraphicsScene* MazeScene;

    // Actions
    QAction *openAct;
    QAction *saveAct;
    QAction *exitAct;
    QAction *optionsAct;
    QAction *actionFullscreen;
    QAction *actionGame_Options;
    QAction *actionWindow_Options;
    QAction *mainMenuRet;

    QColor wallColor;
    QColor pathColor;
    QColor doorColor;
    QColor playerColor;
    QColor enemyColor;

    quint32 nTileWidth;
    quint32 nTileHeight;
    quint32 nBorderWidth;
    quint32 nBorderHeight;

    const QVariant kTile=555;
    const QVariant kPiece=777;
    const quint32 kWidth=45;
};

namespace Ui {
    class MainWindow: public Ui_MazeWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAZEWINDOWRI4129_H
