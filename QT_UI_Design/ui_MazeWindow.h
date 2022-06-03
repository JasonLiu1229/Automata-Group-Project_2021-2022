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
#include <QKeyEvent>
#include <QTimer>
#include <QFormLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QKeySequenceEdit>
#include "../QT_Utils/qtcolorpicker.h"

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
    void setShortcuts();

private slots:

    void slot_new() {newGame();}
    void slot_save() {save();}
    void slot_load() {load();}
    void slot_options() {options();}
    void slot_mainMenu() {mainMenuReturn();}
    void slot_pauseGame() {pauseGame();}
    void slot_showControls() {showControls();}
    void slot_showHelp() {showHelp();}
    void slot_fullScreen() {
//        if (isMaximized()) {
//            showNormal();
//        } else {
//            showMaximized();
//        }
    };
    void slot_level1() {loadLevel(LEV1JSON);}
    void slot_level2() {loadLevel(LEV2JSON);}
    void slot_level3() {loadLevel(LEV3JSON);}
    void slot_level4() {loadLevel(LEV4JSON);}
    void slot_setShortcuts(){setShortcuts();}
    void update();
    void on_actionOptions_triggered();
    void on_actionExit_triggered();

    void closeEvent (QCloseEvent *event) override {
        on_actionExit_triggered();
        event->ignore();
    }

private:

    // Main functionality elements
    Maze* gameLayout;
    QString currentSave;

    // Screen generation functions
    void createActions(QMainWindow *MainWindow);
    void createMenus(QMainWindow *MainWindow);
    void createSelectionScreen(QMainWindow *MainWindow);
    void createLevelScreen(QMainWindow *MainWindow);
    void createOptionsScreen(QMainWindow *MainWindow);

    // Maze visualisation

    void refreshMaze(Maze *&layout);
    void drawMaze(Maze *&layout);
    void drawTile(int i, int j , tileSettings &tileType);
    void drawPlayer(int x , int y);

    void refreshTile(int i , int j , tileSettings &tileType);
    void refreshPlayer(int x , int y);

    quint8 rowFromPoint(int y) const { return static_cast<quint8>(y / nTileWidth); }
    quint8 colFromPoint(int x) const { return static_cast<quint8>(x / nTileHeight); }

    quint32 xFromCol(int c) const { return static_cast<quint32>(c * nTileWidth + 0.5 * nTileWidth); }
    quint32 yFromRow(int r) const { return static_cast<quint32>(r * nTileHeight + 0.5 * nTileHeight); }

    // Main Widgets
    QStackedWidget *MenuScreens;
    QWidget *MainScreen;
    QWidget *LevelSelectionScreen;
    QWidget *levelScreen;
    QWidget *optionsScreen;
    
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

    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QPushButton *mainMenuButton;
    QPushButton *pauseButton;
    QPushButton *HTP_button;
    QPushButton *helpButton;
    QGraphicsView *MazeView;
    QGraphicsScene *MazeScene;

    // Options screen

    QGridLayout *gridLayout_2;

    QGroupBox *VisualisationOptionsBox;
    QFormLayout *formLayout_3;
    QLabel *wallColorLabel;
    QtColorPicker *wallColorPicker;
    QLabel *pathColorLabel;
    QtColorPicker *pathColorPicker;
    QLabel *playerColorLabel;
    QtColorPicker *playerColorPicker;
    QLabel *enemyColorLabel;
    QtColorPicker *enemyColorPicker;
    QLabel *keyColorLabel;
    QtColorPicker *keyColorPicker;
    QLabel *exitColorLabel;
    QtColorPicker *exitColorPicker;

    QGroupBox *KeybindsBox;
    QFormLayout *formLayout_4;
    QLabel *moveUpLabel;
    QKeySequenceEdit *moveUpKeybind;
    QLabel *moveDownLabel;
    QKeySequenceEdit *moveDownKeybind;
    QLabel *moveLeftLabel;
    QKeySequenceEdit *moveLeftKeybind;
    QLabel *moveRightLabel;
    QKeySequenceEdit *moveRightKeybind;
    QPushButton *mainMenuButton_optionsScreen;

    // Actions
    QAction *loadAct;
    QAction *saveAct;
    QAction *exitAct;
    QAction *optionsAct;
    QAction *actionFullscreen;
    QAction *actionGame_Options;
    QAction *mainMenuRet;

    // Shortcuts
    int moveUp;
    int moveDown;
    int moveLeft;
    int moveRight;

    // Visualisation parameters
    QColor wallColor;
    QColor pathColor;
    QColor exitColor;
    QColor playerColor;
    QColor enemyColor;

    quint32 nTileWidth;
    quint32 nTileHeight;
    quint32 nBorderWidth;
    quint32 nBorderHeight;

    const QVariant kTile=555;
    const QVariant kPiece=777;
    const quint32 kWidth=45;

    // Event handling
    void play();
    bool paused;
    QTimer* inputTime;

protected:

    void keyPressEvent(QKeyEvent *k) override;

    bool eventFilter( QObject *o, QEvent *e ) override;

};

namespace Ui {
    class MainWindow: public Ui_MazeWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAZEWINDOWRI4129_H
