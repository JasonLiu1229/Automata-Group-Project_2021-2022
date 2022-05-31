/********************************************************************************
** Form generated from reading UI file 'UI_MazeWindowRI4129.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAZEWINDOWRI4129_H
#define UI_MAZEWINDOWRI4129_H

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
#include <QWidget>
#include <QStackedWidget>
#include <QMainWindow>
#include <QMessageBox>
#include <QAction>
#include <QCloseEvent>
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

private slots:

    void slot_new() {newGame();}
    void slot_open() {open();}
    void slot_save() {save();}
    void slot_load() {load();}
    void slot_options() {options();}
    void slot_mainMenu() {mainMenuReturn();}
    void slot_fullScreen() {
        if (isMaximized()) {
            showNormal();
        } else {
            showMaximized();
        }
    };

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
    // Main Widgets
    QStackedWidget *MenuScreens;
    QWidget *MainScreen;
    QWidget *LevelSelectionScreen;


    // Level selection screen
    QGridLayout *LevelsGrid;
    QPushButton *Level3;
    QPushButton *Level4;
    QPushButton *Level1;
    QPushButton *Level2;
    QPushButton *MenuButton;
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
    // Actions
    QAction *openAct;
    QAction *saveAct;
    QAction *exitAct;
    QAction *optionsAct;
    QAction *actionFullscreen;
    QAction *actionGame_Options;
    QAction *mainMenuRet;
    QAction *actionWindow_Options;
};

namespace Ui {
    class MainWindow: public Ui_MazeWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAZEWINDOWRI4129_H
