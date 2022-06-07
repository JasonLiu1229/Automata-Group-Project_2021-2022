#include <iostream>
#include <qmainwindow.h>
#include <QtWidgets>
#include <QGraphicsDropShadowEffect>
#include <qnamespace.h>
#include "ui_MazeWindow.h"
#include "../Parser.h"
#include "../Maze.h"
#include "../Path.h"
using namespace std;
using namespace Ui;


void Ui_MazeWindow::setupUi(QMainWindow *MainWindow)
{
    // Setup window
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName(QString::fromUtf8("MainWindow"));

    MainWindow->resize(1024, 720);
    MainWindow->setMinimumSize(QSize(852, 450));
    MainWindow->setMaximumSize(QSize(1336, 1080));
    MainWindow->setSizeIncrement(QSize(10, 10));
    MainWindow->setBaseSize(QSize(1024, 720));
    MainWindow->setFocusPolicy(Qt::NoFocus);
    MainWindow->setTabShape(QTabWidget::Rounded);

    // Set parameters

    paused = false;
    currentSave = "";
    moveUp = Qt::Key_W;
    moveLeft = Qt::Key_A;
    moveRight = Qt::Key_D;
    moveDown = Qt::Key_S;

    nTileWidth = kWidth;
    nTileHeight = kWidth;

    wallColor = Qt::black;
    pathColor = Qt::gray;
    exitColor = QColor(150,75,0);
    playerColor = Qt::white;
    enemyColor = QColor(138,3,3);
    keyColor = QColor(250,250,0);

//    wallColorN = wallColor.name();
//    pathColorN = pathColor.name();
//    playerColorN = playerColor.name();
//    enemyColorN = enemyColor.name();
//    keyColorN = keyColor.name();
//    exitColorN = exitColor.name();

    // Create actions
    createActions(MainWindow);
    // Create menus
    createMenus(MainWindow);
    // Retranslate
    retranslateUi(MainWindow);

    inputTime = new QTimer;
    enemyTime = new QTimer;
    playerdead = new QTimer;
    connect(inputTime, &QTimer::timeout, this, QOverload<>::of(&Ui_MazeWindow::update));
    connect(enemyTime,&QTimer::timeout, this, QOverload<>::of(&Ui_MazeWindow::EnemyMovement));
    connect(playerdead,&QTimer::timeout, this, QOverload<>::of(&Ui_MazeWindow::playergone));
    inputTime->stop();
    enemyTime->stop();
    playerdead->stop();
    fog = false;
}

void Ui_MazeWindow::retranslateUi(QMainWindow *MainWindow)
{
    MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Untitled Maze Game", nullptr));

#ifndef QT_NO_ACCESSIBILITY
    MainWindow->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY

    loadAct->setText(QApplication::translate("MainWindow", "Load", nullptr));
    saveAct->setText(QApplication::translate("MainWindow", "Save", nullptr));
    exitAct->setText(QApplication::translate("MainWindow", "Exit", nullptr));
    showScoresAct->setText(QApplication::translate("MainWindow", "Highscores", nullptr));
    actionFullscreen->setText(QApplication::translate("MainWindow", "Fullscreen", nullptr));
    actionFullscreen->setShortcut(QApplication::translate("MainWindow", "Ctrl+F", nullptr));
    actionGame_Options->setText(QApplication::translate("MainWindow", "Game Options", nullptr));
    newGameButton->setText(QApplication::translate("MainWindow", "New Game", nullptr));
    LoadGameButton->setText(QApplication::translate("MainWindow", "Load Game", nullptr));
    OptionsButton->setText(QApplication::translate("MainWindow", "Options", nullptr));
    ExitButton->setText(QApplication::translate("MainWindow", "Exit", nullptr));
    menuFile->setTitle(QApplication::translate("MainWindow", "File", nullptr));
    menuOptions->setTitle(QApplication::translate("MainWindow", "Options", nullptr));
    fogEnabledAct->setText(QApplication::translate("MainWindow", "Fog of War", nullptr));
    fogEnabledAct->setShortcut(QApplication::translate("MainWindow", "Alt+F", nullptr));
}

QString Ui_MazeWindow::getColorName(QColor &color) {
    QColor cmp;
    for(const auto &i : QColor::colorNames()) {
        cmp.setNamedColor(i);
        if(cmp == color){
            return i;
        }
    }
    return color.name();
}

void Ui_MazeWindow::setColorNames() {
    wallColorN = wallColor.name();
    pathColorN = pathColor.name();
    playerColorN = playerColor.name();
    enemyColorN = enemyColor.name();
    keyColorN = keyColor.name();
    exitColorN = exitColor.name();
}

void Ui_MazeWindow::setShortcuts() {
    if(!moveUpKeybind->keySequence().isEmpty()){
        moveUp = moveUpKeybind->keySequence()[0];
    }
//    moveUpKeybind->clear();
    if(!moveDownKeybind->keySequence().isEmpty()){
        moveDown = moveDownKeybind->keySequence()[0];
    }
//    moveDownKeybind->clear();
    if(!moveLeftKeybind->keySequence().isEmpty()){
        moveLeft = moveLeftKeybind->keySequence()[0];
    }
//    moveLeftKeybind->clear();
    if(!moveRightKeybind->keySequence().isEmpty()){
        moveRight = moveRightKeybind->keySequence()[0];
    }
//    moveRightKeybind->clear();
    if(!fogKeybind->keySequence().isEmpty()){
        fogEnabledAct->setShortcut(fogKeybind->keySequence()[0]);
    }
}

void Ui_MazeWindow::setColours() {
    wallColor;
    pathColor;
    exitColor;
    playerColor;
    enemyColor;
    keyColor;
}

QString Ui_MazeWindow::getStylesheet(QString &ref) {
    string color;
    QString newCol;
    color = "QPushButton {background-color:" ;
    color += ref.toStdString();
    color += ";color:";
    if (ref.toStdString() != "" && ref.toStdString() != "#ffffff") {
        color += "white";
    }
    else {
        color += "black";
    }
    color += ";}";
    newCol = QString::fromStdString(color);
    return newCol;
}

void Ui_MazeWindow::createActions(QMainWindow *MainWindow) {

    loadAct = new QAction(tr("&Load"), this);
    loadAct->setShortcuts(QKeySequence::Open);
    loadAct->setStatusTip(tr("Read game from disk"));
    connect(loadAct, &QAction::triggered, this, &Ui_MazeWindow::slot_load);

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save game to disk"));
    connect(saveAct, &QAction::triggered, this, &Ui_MazeWindow::slot_save);

    showScoresAct = new QAction(tr("&Highscores"), this);
    showScoresAct->setObjectName(QString::fromUtf8("showScoresAct"));
    showScoresAct->setStatusTip(tr("Show highscores"));
    connect(showScoresAct , &QAction::triggered , this , &Ui_MazeWindow::slot_scoreBoard);

    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Abandon game"));
    connect(exitAct, &QAction::triggered, this, &Ui_MazeWindow::on_actionExit_triggered);

    actionFullscreen = new QAction(MainWindow);
    actionFullscreen->setObjectName(QString::fromUtf8("actionFullscreen"));
    actionFullscreen->setCheckable(true);
    connect(actionFullscreen , &QAction::triggered , this, &Ui_MazeWindow::slot_fullScreen);

    actionGame_Options = new QAction(MainWindow);
    actionGame_Options->setObjectName(QString::fromUtf8("actionGame_Options"));
    connect(actionGame_Options , &QAction::triggered , this , &Ui_MazeWindow::slot_options);

    mainMenuRet = new QAction(MainWindow);
    mainMenuRet->setObjectName(QString::fromUtf8("mainMenuRet"));
    connect(mainMenuRet , &QAction::triggered , this , &Ui_MazeWindow::slot_mainMenu);

    fogEnabledAct = new QAction(MainWindow);
    fogEnabledAct->setObjectName(QString::fromUtf8("fogEnabled"));
    fogEnabledAct->setCheckable(true);
    connect(fogEnabledAct , &QAction::triggered , this , &Ui_MazeWindow::slot_fogEnabled);
}

void Ui_MazeWindow::createMenus(QMainWindow *MainWindow) {

    // Size policy
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);

    MenuScreens = new QStackedWidget(MainWindow);

    MainScreen = new QWidget(MainWindow);
    MainScreen->setObjectName(QString::fromUtf8("MainScreen"));

    verticalLayoutWidget = new QWidget(MainScreen);
    verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
    verticalLayoutWidget->setGeometry(QRect(0, 90, 1021, 581));

    MainScreenLayout = new QVBoxLayout(verticalLayoutWidget);
    MainScreenLayout->setSpacing(100);
    MainScreenLayout->setObjectName(QString::fromUtf8("MainScreenLayout"));
    MainScreenLayout->setContentsMargins(400, 1, 400, 1);

    newGameButton = new QPushButton(verticalLayoutWidget);
    newGameButton->setObjectName(QString::fromUtf8("newGameButton"));
    sizePolicy.setHeightForWidth(newGameButton->sizePolicy().hasHeightForWidth());
    newGameButton->setSizePolicy(sizePolicy);
    connect(newGameButton, SIGNAL(clicked()), this, SLOT(slot_new()) );


    LoadGameButton = new QPushButton(verticalLayoutWidget);
    LoadGameButton->setObjectName(QString::fromUtf8("LoadGameButton"));
    sizePolicy.setHeightForWidth(LoadGameButton->sizePolicy().hasHeightForWidth());
    LoadGameButton->setSizePolicy(sizePolicy);
    connect(LoadGameButton, SIGNAL(clicked()), this, SLOT(slot_load() ) );


    OptionsButton = new QPushButton(verticalLayoutWidget);
    OptionsButton->setObjectName(QString::fromUtf8("OptionsButton"));
    sizePolicy.setHeightForWidth(OptionsButton->sizePolicy().hasHeightForWidth());
    OptionsButton->setSizePolicy(sizePolicy);
    connect(OptionsButton, SIGNAL(clicked()), this, SLOT(slot_options() ) );


    ExitButton = new QPushButton(verticalLayoutWidget);
    ExitButton->setObjectName(QString::fromUtf8("ExitButton"));
    ExitButton->setShortcut(QKeySequence::Quit);
    ExitButton->addAction(exitAct);
    sizePolicy.setHeightForWidth(ExitButton->sizePolicy().hasHeightForWidth());
    ExitButton->setSizePolicy(sizePolicy);
    connect(ExitButton, SIGNAL(clicked()), this, SLOT(on_actionExit_triggered()));


    MainScreenLayout->addWidget(newGameButton);
    MainScreenLayout->addWidget(LoadGameButton);
    MainScreenLayout->addWidget(OptionsButton);
    MainScreenLayout->addWidget(ExitButton);

    MenuScreens->addWidget(MainScreen);
    MenuScreens->setCurrentWidget(MainScreen);

    // Create different screens
    createSelectionScreen(MainWindow);
    createLevelScreen(MainWindow);
    createOptionsScreen(MainWindow);
    createGameOverScreen(MainWindow);

    MenuScreens->addWidget(LevelSelectionScreen);
    MenuScreens->addWidget(levelScreen);
    MenuScreens->addWidget(optionsScreen);
    MenuScreens->addWidget(gameOverScreen);

    MainWindow->setCentralWidget(MenuScreens);



    menubar = new QMenuBar(MainWindow);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 1024, 24));

    menuFile = new QMenu(menubar);
    menuFile->setObjectName(QString::fromUtf8("menuFile"));

    menuOptions = new QMenu(menubar);
    menuOptions->setObjectName(QString::fromUtf8("menuOptions"));

    MainWindow->setMenuBar(menubar);
    statusbar = new QStatusBar(MainWindow);
    statusbar->setObjectName(QString::fromUtf8("statusBar"));
    keyStatusLabel = new QLabel(this);
    keyStatusLabel->setText("Remaining keys: ");
    keyNumber = new QLCDNumber(this);
    keyNumber->setMode(QLCDNumber::Dec);
//    keyNumber->setSegmentStyle(QLCDNumber::Flat);
    keyNumber->display(0);
    doorStatusLabel = new QLabel(this);
    doorStatusLabel->setText("Door Locked");
    timeLabel = new QLabel(this);
    timeLabel->setText("Time: ");
    levelTime = new QLCDNumber(this);
    levelTime->setSegmentStyle(QLCDNumber::Flat);
    statusbar->addPermanentWidget(keyStatusLabel);
    statusbar->addPermanentWidget(keyNumber);
    statusbar->addPermanentWidget(timeLabel);
    statusbar->addPermanentWidget(levelTime);
    statusbar->addPermanentWidget(doorStatusLabel);
    statusbar->hide();
    MainWindow->setStatusBar(statusbar);

    menubar->addAction(menuFile->menuAction());
    menubar->addAction(menuOptions->menuAction());
    menuFile->addAction(loadAct);
    menuFile->addAction(saveAct);
    menuFile->addAction(showScoresAct);
    menuFile->addAction(exitAct);
    menuOptions->addAction(actionFullscreen);
    menuOptions->addAction(fogEnabledAct);
    menuOptions->addAction(actionGame_Options);

}

void Ui_MazeWindow::createSelectionScreen(QMainWindow *MainWindow) {

    LevelSelectionScreen = new QWidget(MainWindow);
    LevelSelectionScreen->setObjectName(QString::fromUtf8("LevelSelectionScreen"));
    LevelSelectionScreen->setGeometry(QRect(0, 120, 1024, 720));

    LevelsGrid = new QGridLayout(LevelSelectionScreen);
    LevelsGrid->setSpacing(100);
    LevelsGrid->setObjectName(QString::fromUtf8("LevelsGrid"));
    LevelsGrid->setSizeConstraint(QLayout::SetDefaultConstraint);
    LevelsGrid->setContentsMargins(75, 75, 75, 25);

    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    LevelSelectionScreen->setSizePolicy(sizePolicy);

    Level1 = new QPushButton(LevelSelectionScreen);
    Level1->setObjectName(QString::fromUtf8("Level1"));
    sizePolicy.setHeightForWidth(Level1->sizePolicy().hasHeightForWidth());
    Level1->setSizePolicy(sizePolicy);

    Level2 = new QPushButton(LevelSelectionScreen);
    Level2->setObjectName(QString::fromUtf8("Level2"));
    sizePolicy.setHeightForWidth(Level2->sizePolicy().hasHeightForWidth());
    Level2->setSizePolicy(sizePolicy);

    Level3 = new QPushButton(LevelSelectionScreen);
    Level3->setObjectName(QString::fromUtf8("Level3"));
    sizePolicy.setHeightForWidth(Level3->sizePolicy().hasHeightForWidth());
    Level3->setSizePolicy(sizePolicy);

    Level4 = new QPushButton(LevelSelectionScreen);
    Level4->setObjectName(QString::fromUtf8("Level4"));
    sizePolicy.setHeightForWidth(Level4->sizePolicy().hasHeightForWidth());
    Level4->setSizePolicy(sizePolicy);


    MenuButton = new QPushButton(LevelSelectionScreen);
    MenuButton->setObjectName(QString::fromUtf8("MenuButton"));
    MenuButton->setGeometry(QRect(75, 25, 100, 25));

    LevelsGrid->addWidget(Level1, 0, 0, 1, 1);
    LevelsGrid->addWidget(Level2, 0, 1, 1, 1);
    LevelsGrid->addWidget(Level3, 1, 0, 1, 1);
    LevelsGrid->addWidget(Level4, 1, 1, 1, 1);


    Level3->setText(QApplication::translate("MainWindow", "Level 3", nullptr));
    Level4->setText(QApplication::translate("MainWindow", "Level 4", nullptr));
    Level1->setText(QApplication::translate("MainWindow", "Level 1", nullptr));
    Level2->setText(QApplication::translate("MainWindow", "Level 2", nullptr));

    MenuButton->setText(QApplication::translate("MainWindow", "Main menu", nullptr));

    connect(MenuButton, SIGNAL(clicked()), this, SLOT( slot_mainMenu() ) );
    connect(Level1, SIGNAL(clicked()), this, SLOT( slot_level1() ) );
    connect(Level2, SIGNAL(clicked()), this, SLOT( slot_level2() ) );
    connect(Level3, SIGNAL(clicked()), this, SLOT( slot_level3() ) );
    connect(Level4, SIGNAL(clicked()), this, SLOT( slot_level4() ) );

}

void Ui_MazeWindow::createLevelScreen(QMainWindow *MainWindow){

    // Create new widget
    levelScreen = new QWidget(MainWindow);
    levelScreen->setObjectName(QString::fromUtf8("levelScreen"));

    // Create layouts
    horizontalLayout_2 = new QHBoxLayout(levelScreen);
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    verticalLayout = new QVBoxLayout();
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));

    // Create buttons
    mainMenuButton = new QPushButton(levelScreen);
    mainMenuButton->setObjectName(QString::fromUtf8("mainMenuButton"));

    pauseButton = new QPushButton(levelScreen);
    pauseButton->setObjectName(QString::fromUtf8("pauseButton"));

    HTP_button = new QPushButton(levelScreen);
    HTP_button->setObjectName(QString::fromUtf8("HTP_button"));

    helpButton = new QPushButton(levelScreen);
    helpButton->setObjectName(QString::fromUtf8("helpButton"));

    // Add buttons to layouts
    horizontalLayout->addWidget(mainMenuButton);
    horizontalLayout->addWidget(pauseButton);
    horizontalLayout->addWidget(HTP_button);
    horizontalLayout->addWidget(helpButton);
    verticalLayout->addLayout(horizontalLayout);

    // Create GraphicView
    MazeView = new QGraphicsView(levelScreen);
    MazeView->setObjectName(QString::fromUtf8("MazeView"));

    verticalLayout->addWidget(MazeView);
    horizontalLayout_2->addLayout(verticalLayout);

    // Retranslate buttons
    mainMenuButton->setText(QApplication::translate("MainWindow", "Main menu", nullptr));
    pauseButton->setText(QApplication::translate("MainWindow", "Pause", nullptr));
    HTP_button->setText(QApplication::translate("MainWindow", "How to play", nullptr));
    helpButton->setText(QApplication::translate("MainWindow", "Help", nullptr));

    // Connect buttons to slots
    connect(mainMenuButton , SIGNAL(clicked()) , this , SLOT(slot_mainMenu()) );
    connect(pauseButton , SIGNAL(clicked()) , this , SLOT(slot_pauseGame()) );
    connect(HTP_button , SIGNAL(clicked()) , this , SLOT(slot_showControls()) );
    connect(helpButton , SIGNAL(clicked()) , this , SLOT(slot_showHelp()) );

    levelScreen->setEnabled(true);

}

void Ui_MazeWindow::createOptionsScreen(QMainWindow *MainWindow) {

    setColorNames();
    string color;
    QString newCol;
    // Create new widget
    optionsScreen = new QWidget(MainWindow);
    optionsScreen->setObjectName(QString::fromUtf8("OptionsScreen"));

    gridLayout_2 = new QGridLayout(optionsScreen);
    gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
    VisualisationOptionsBox = new QGroupBox(optionsScreen);
    VisualisationOptionsBox->setObjectName(QString::fromUtf8("VisualisationOptionsBox"));
    VisualisationOptionsBox->setFlat(false);
    VisualisationOptionsBox->setCheckable(false);
    VisualisationOptionsBox->setChecked(false);
    formLayout_3 = new QFormLayout(VisualisationOptionsBox);
    formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
    formLayout_3->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
    wallColorLabel = new QLabel(VisualisationOptionsBox);
    wallColorLabel->setObjectName(QString::fromUtf8("wallColorLabel"));

    formLayout_3->setWidget(0, QFormLayout::LabelRole, wallColorLabel);

    wallColorPicker = new QPushButton(VisualisationOptionsBox);
    wallColorPicker->setObjectName(QString::fromUtf8("wallColorPicker"));
    wallColorPicker->setStyleSheet(getStylesheet(wallColorN));
    wallColorPicker->setText(wallColorN);

    formLayout_3->setWidget(0, QFormLayout::FieldRole, wallColorPicker);

    pathColorLabel = new QLabel(VisualisationOptionsBox);
    pathColorLabel->setObjectName(QString::fromUtf8("pathColorLabel"));

    formLayout_3->setWidget(1, QFormLayout::LabelRole, pathColorLabel);

    pathColorPicker = new QPushButton(VisualisationOptionsBox);
    pathColorPicker->setObjectName(QString::fromUtf8("pathColorPicker"));
    pathColorPicker->setStyleSheet(getStylesheet(pathColorN));
    pathColorPicker->setText(pathColorN);

    formLayout_3->setWidget(1, QFormLayout::FieldRole, pathColorPicker);

    playerColorLabel = new QLabel(VisualisationOptionsBox);
    playerColorLabel->setObjectName(QString::fromUtf8("playerColorLabel"));

    formLayout_3->setWidget(2, QFormLayout::LabelRole, playerColorLabel);

    playerColorPicker = new QPushButton(VisualisationOptionsBox);
    playerColorPicker->setObjectName(QString::fromUtf8("playerColorPicker"));
    playerColorPicker->setStyleSheet(getStylesheet(playerColorN));
    playerColorPicker->setText(playerColorN);

    formLayout_3->setWidget(2, QFormLayout::FieldRole, playerColorPicker);

    enemyColorLabel = new QLabel(VisualisationOptionsBox);
    enemyColorLabel->setObjectName(QString::fromUtf8("enemyColorLabel"));

    formLayout_3->setWidget(3, QFormLayout::LabelRole, enemyColorLabel);

    enemyColorPicker = new QPushButton(VisualisationOptionsBox);
    enemyColorPicker->setObjectName(QString::fromUtf8("enemyColorPicker"));
    enemyColorPicker->setStyleSheet(getStylesheet(enemyColorN));
    enemyColorPicker->setText(enemyColorN);


    formLayout_3->setWidget(3, QFormLayout::FieldRole, enemyColorPicker);

    keyColorLabel = new QLabel(VisualisationOptionsBox);
    keyColorLabel->setObjectName(QString::fromUtf8("keyColorLabel"));

    formLayout_3->setWidget(4, QFormLayout::LabelRole, keyColorLabel);

    keyColorPicker = new QPushButton(VisualisationOptionsBox);
    keyColorPicker->setObjectName(QString::fromUtf8("keyColorPicker"));
    keyColorPicker->setStyleSheet(getStylesheet(keyColorN));
    keyColorPicker->setText(keyColorN);


    formLayout_3->setWidget(4, QFormLayout::FieldRole, keyColorPicker);

    exitColorLabel = new QLabel(VisualisationOptionsBox);
    exitColorLabel->setObjectName(QString::fromUtf8("exitColorLabel"));

    formLayout_3->setWidget(5, QFormLayout::LabelRole, exitColorLabel);

    exitColorPicker = new QPushButton(VisualisationOptionsBox);
    exitColorPicker->setObjectName(QString::fromUtf8("exitColorPicker"));
    exitColorPicker->setStyleSheet(getStylesheet(exitColorN));
    exitColorPicker->setText(exitColorN);

    formLayout_3->setWidget(5, QFormLayout::FieldRole, exitColorPicker);

    saveColorChoice = new QPushButton(VisualisationOptionsBox);
    saveColorChoice->setObjectName(QString::fromUtf8("saveColorChoice"));
    saveColorChoice->setText("Save");

    formLayout_3->setWidget(6 , QFormLayout::FieldRole , saveColorChoice);

    gridLayout_2->addWidget(VisualisationOptionsBox, 1, 0, 1, 1);

    KeybindsBox = new QGroupBox(optionsScreen);
    KeybindsBox->setObjectName(QString::fromUtf8("KeybindsBox"));
    formLayout_4 = new QFormLayout(KeybindsBox);
    formLayout_4->setObjectName(QString::fromUtf8("formLayout_4"));
    formLayout_4->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
    moveUpLabel = new QLabel(KeybindsBox);
    moveUpLabel->setObjectName(QString::fromUtf8("moveUpLabel"));

    formLayout_4->setWidget(0, QFormLayout::LabelRole, moveUpLabel);

    moveUpKeybind = new QKeySequenceEdit(KeybindsBox);
    moveUpKeybind->setObjectName(QString::fromUtf8("moveUpKeybind"));

    formLayout_4->setWidget(0, QFormLayout::FieldRole, moveUpKeybind);

    moveDownLabel = new QLabel(KeybindsBox);
    moveDownLabel->setObjectName(QString::fromUtf8("moveDownLabel"));

    formLayout_4->setWidget(1, QFormLayout::LabelRole, moveDownLabel);

    moveDownKeybind = new QKeySequenceEdit(KeybindsBox);
    moveDownKeybind->setObjectName(QString::fromUtf8("moveDownKeybind"));

    formLayout_4->setWidget(1, QFormLayout::FieldRole, moveDownKeybind);

    moveLeftLabel = new QLabel(KeybindsBox);
    moveLeftLabel->setObjectName(QString::fromUtf8("moveLeftLabel"));

    formLayout_4->setWidget(2, QFormLayout::LabelRole, moveLeftLabel);

    moveLeftKeybind = new QKeySequenceEdit(KeybindsBox);
    moveLeftKeybind->setObjectName(QString::fromUtf8("moveLeftKeybind"));

    formLayout_4->setWidget(2, QFormLayout::FieldRole, moveLeftKeybind);

    moveRightLabel = new QLabel(KeybindsBox);
    moveRightLabel->setObjectName(QString::fromUtf8("moveRightLabel"));

    formLayout_4->setWidget(3, QFormLayout::LabelRole, moveRightLabel);

    moveRightKeybind = new QKeySequenceEdit(KeybindsBox);
    moveRightKeybind->setObjectName(QString::fromUtf8("moveRightKeybind"));

    formLayout_4->setWidget(3, QFormLayout::FieldRole, moveRightKeybind);

    fogShortcutLabel = new QLabel(KeybindsBox);
    fogShortcutLabel->setObjectName(QString::fromUtf8("fogShortcutLabel"));

    formLayout_4->setWidget(4, QFormLayout::LabelRole, fogShortcutLabel);

    fogKeybind = new QKeySequenceEdit(KeybindsBox);
    fogKeybind->setObjectName(QString::fromUtf8("fogKeybind"));

    formLayout_4->setWidget(4, QFormLayout::FieldRole, fogKeybind);

    saveKeybindsButton = new QPushButton(KeybindsBox);
    saveKeybindsButton->setObjectName(QString::fromUtf8("saveKeybindsButton"));

    formLayout_4->setWidget(5, QFormLayout::LabelRole, saveKeybindsButton);


    gridLayout_2->addWidget(KeybindsBox, 1, 1, 1, 1);

    mainMenuButton_optionsScreen = new QPushButton(optionsScreen);
    mainMenuButton_optionsScreen->setObjectName(QString::fromUtf8("mainMenuButton_optionsScreen"));

    gridLayout_2->addWidget(mainMenuButton_optionsScreen, 0, 0, 1, 1);

    // Retranslate UI

    optionsScreen->setWindowTitle(QApplication::translate("OptionsScreen", "Form", nullptr));
    VisualisationOptionsBox->setTitle(QApplication::translate("OptionsScreen", "Visualisation Options", nullptr));
    wallColorLabel->setText(QApplication::translate("OptionsScreen", "Wall color", nullptr));
    pathColorLabel->setText(QApplication::translate("OptionsScreen", "Path color", nullptr));
    playerColorLabel->setText(QApplication::translate("OptionsScreen", "Player color", nullptr));
    enemyColorLabel->setText(QApplication::translate("OptionsScreen", "Enemy color", nullptr));
    keyColorLabel->setText(QApplication::translate("OptionsScreen", "Key color", nullptr));
    exitColorLabel->setText(QApplication::translate("OptionsScreen", "Exit color", nullptr));
    KeybindsBox->setTitle(QApplication::translate("OptionsScreen", "Keybinds", nullptr));
    moveUpLabel->setText(QApplication::translate("OptionsScreen", "Move up", nullptr));
    moveDownLabel->setText(QApplication::translate("OptionsScreen", "Move down", nullptr));
    moveLeftLabel->setText(QApplication::translate("OptionsScreen", "Move left", nullptr));
    moveRightLabel->setText(QApplication::translate("OptionsScreen", "Move right", nullptr));
    fogShortcutLabel->setText(QApplication::translate("OptionsScreen", "Fog of War", nullptr));
    saveKeybindsButton->setText(QApplication::translate("OptionsScreen" , "Save" , nullptr));
    mainMenuButton_optionsScreen->setText(QApplication::translate("OptionsScreen", "Main Menu", nullptr));

    // Connect buttons to slots
    connect( mainMenuButton_optionsScreen , SIGNAL(clicked()) , this , SLOT( slot_mainMenu() ) );
    connect( saveKeybindsButton , SIGNAL(clicked()) , this , SLOT( slot_setShortcuts() ) );
    connect( saveColorChoice , SIGNAL(clicked()) , this , SLOT( slot_setColours() ) );

}

void Ui_MazeWindow::createGameOverScreen(QMainWindow *MainWindow) {
    // Create new widget
    gameOverScreen = new QWidget(MainWindow);
    gameOverScreen->setObjectName(QString::fromUtf8("gameOverScreen"));
    verticalLayout_3 = new QVBoxLayout(gameOverScreen);
    verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
    horizontalLayout_4 = new QHBoxLayout();
    horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
    mainMenuButton_3 = new QPushButton(gameOverScreen);
    mainMenuButton_3->setObjectName(QString::fromUtf8("mainMenuButton_3"));

    horizontalLayout_4->addWidget(mainMenuButton_3);

    newGameButton_2 = new QPushButton(gameOverScreen);
    newGameButton_2->setObjectName(QString::fromUtf8("newGameButton"));

    horizontalLayout_4->addWidget(newGameButton_2);


    verticalLayout_3->addLayout(horizontalLayout_4);

    gameOverlabel = new QLabel(gameOverScreen);
    gameOverlabel->setObjectName(QString::fromUtf8("gameOverlabel"));
    QFont font;
    font.setBold(true);
    font.setItalic(true);
    font.setUnderline(false);
    font.setWeight(75);
    gameOverlabel->setFont(font);
    gameOverlabel->setAlignment(Qt::AlignCenter);

    verticalLayout_3->addWidget(gameOverlabel);

    gameOverphoto = new QLabel(gameOverScreen);
    gameOverphoto->setObjectName(QString::fromUtf8("gameOverphoto"));
    gameOverphoto->setPixmap(QPixmap(QString::fromUtf8("../../Photos/GameOver.png")));
    gameOverphoto->setScaledContents(true);

    verticalLayout_3->addWidget(gameOverphoto);

    MenuScreens->addWidget(gameOverScreen);

    gameOverlabel->setText(QApplication::translate("MainWindow", "Game Over", nullptr));
    mainMenuButton_3->setText(QApplication::translate("MainWindow", "Main menu", nullptr));
    newGameButton_2->setText(QApplication::translate("MainWindow", "New Game", nullptr));
    gameOverphoto->setText(QString());

    connect(mainMenuButton_3 , SIGNAL(clicked()) , this , SLOT(slot_mainMenu()));
    connect(newGameButton_2 , SIGNAL(clicked()) , this , SLOT(slot_new()));

}

void Ui_MazeWindow::on_actionOptions_triggered() {

}

void Ui_MazeWindow::on_actionExit_triggered() {
    if (QMessageBox::Yes == QMessageBox::question(this,
                                                  tr("Exit game"),
                                                  tr("Are you sure you want to exit the game?\nUnsaved data will be lost.")))
    {
        QApplication::quit();
    }
}

void Ui_MazeWindow::newGame() {
    MenuScreens->setCurrentWidget(LevelSelectionScreen);
}

void Ui_MazeWindow::save() {
    if(gameLayout != nullptr){
        if(currentSave == ""){
            // From official QT doc https://doc.qt.io/qt-5/qfiledialog.html#fileMode-prop
            currentSave = QFileDialog::getSaveFileName(this , "Save game" , SVG1 , "MazeSave (*.txt)");
            gameLayout->setSavedFile("");
            gameLayout->Save(currentSave.toStdString());
            // Update save file
            currentSave = QString::fromStdString(gameLayout->getSavedFile());
        }
        else{
            gameLayout->Save();
            currentSave = QString::fromStdString(gameLayout->getSavedFile());
        }
    }
}

void Ui_MazeWindow::load() {

    QString loadSave = QFileDialog::getOpenFileName(this , "Open save" , SVG1 , "MazeSave (*.json)");
    if(!loadSave.toStdString().empty()){
        Parser* parser = new Parser(loadSave.toStdString());
        loadLevel(loadSave.toStdString());
    }
}

void Ui_MazeWindow::options() {
    statusbar->hide();
    pauseButton->setText("Pause");
    paused = false;
    MenuScreens->setCurrentWidget(optionsScreen);
}

void Ui_MazeWindow::mainMenuReturn() {
    statusbar->hide();
    this->releaseKeyboard();
    pauseButton->setText("Pause");
    paused = false;
    MenuScreens->setCurrentWidget(MainScreen);
}

void Ui_MazeWindow::showScoreboard() {
    statusbar->hide();
    pauseButton->setText("Pause");
    paused = false;
    MenuScreens->setCurrentWidget(scoreboardScreen);
}

void Ui_MazeWindow::loadLevel(string filename){
    // Initialize parser
    Parser* parser = new Parser(filename);
    // Create maze
    gameLayout = new Maze();
    // Load maze
    gameLayout->loadGame(parser->getTxt_Filename());
    gameLayout->setSavedFile(parser->getTxt_Filename());

    MenuScreens->setCurrentWidget(levelScreen);
    // Create Graphics Scene
    MazeScene = new QGraphicsScene(MazeView);
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
        // Draw the maze(make all the tiles)
    update();
    // Set the scene
    MazeView->setScene(MazeScene);
    // Change the window view
    delete parser;

    inputTime->start(25);
    playerdead->start(0);
    enemyTime->start(300);

    MazeView->setFocus();
    this->grabKeyboard();
    statusbar->show();
    paused = false;
}

void Ui_MazeWindow::pauseGame() {

    paused = !paused;
    if(paused){
        inputTime->stop();
        playerdead->stop();
        enemyTime->stop();
        pauseButton->setText("Resume");
    }
    else{
        play();
        pauseButton->setText("Pause");
    }
}

void Ui_MazeWindow::showControls() {
    cout << "Show Controls option" << endl;
}

void Ui_MazeWindow::showHelp() {
    cout << "Show Help option" << endl;
}

void Ui_MazeWindow::update() {
    auto width =  MazeView->width() / gameLayout->getWidth();
    auto height = MazeView->height() / gameLayout->getHeight();
    nTileWidth = static_cast<quint32>(width);
    nTileHeight = static_cast<quint32>(height);
    if(!paused){
        refreshMaze(gameLayout);
    }
    int key_count = gameLayout->getKey_count();
    keyNumber->display(key_count);
    if(gameLayout->getDFAkeys()->getCurrentState()->getkeystate()){
        doorStatusLabel->setText("Door Unlocked");
    }
    else{
        doorStatusLabel->setText("Door Locked");
    }
}

void Ui_MazeWindow::refreshMaze(Maze *&layout) {
    qDeleteAll( MazeScene->items());
    drawMaze(layout);
}

void Ui_MazeWindow::drawMaze(Maze *&layout) {
    Path* currentTile;
    tileSettings setting;
    for(int i=0; i<layout->getWidth(); i++)
    {
        for(int j=0; j<layout->getHeight(); j++)
        {
            currentTile = layout->getPath(i,j);
            setting = currentTile->getSettings();
            if(!fog){
                if(currentTile->isStarting()) {
                    drawPlayer(i , j);
                }
                else if(currentTile->isEnemy()){
                    drawenemy(i,j);
                }
                else if(currentTile->isKey()){
                    drawkey(i,j);
                }
                else if(currentTile->isAccepting() and gameLayout->getDFAkeys()->getCurrentState()->getkeystate()){
                    drawescape(i,j);
                }
                else {
                    drawTile(i,j,setting);
                }
            }
            else{
                if(currentTile->isStarting()) {
                    drawPlayer(i , j);
                }
                else if(currentTile == gameLayout->getPlayer()->getCurrentTile()->getUp()){
                    if(currentTile->isEnemy()){
                        drawenemy(i,j);
                    }
                    else if(currentTile->isKey()){
                        drawkey(i,j);
                    }
                    else if(currentTile->isAccepting() and gameLayout->getDFAkeys()->getCurrentState()->getkeystate()){
                        drawescape(i,j);
                    }
                    else {
                        drawTile(i,j,setting);
                    }
                }
                else if(currentTile == gameLayout->getPlayer()->getCurrentTile()->getLeft()){
                    if(currentTile->isEnemy()){
                        drawenemy(i,j);
                    }
                    else if(currentTile->isKey()){
                        drawkey(i,j);
                    }
                    else if(currentTile->isAccepting() and gameLayout->getDFAkeys()->getCurrentState()->getkeystate()){
                        drawescape(i,j);
                    }
                    else {
                        drawTile(i,j,setting);
                    }
                }
                else if(currentTile == gameLayout->getPlayer()->getCurrentTile()->getDown()){
                    if(currentTile->isEnemy()){
                        drawenemy(i,j);
                    }
                    else if(currentTile->isKey()){
                        drawkey(i,j);
                    }
                    else if(currentTile->isAccepting() and gameLayout->getDFAkeys()->getCurrentState()->getkeystate()){
                        drawescape(i,j);
                    }
                    else {
                        drawTile(i,j,setting);
                    }
                }
                else if(currentTile == gameLayout->getPlayer()->getCurrentTile()->getRight()){
                    if(currentTile->isEnemy()){
                        drawenemy(i,j);
                    }
                    else if(currentTile->isKey()){
                        drawkey(i,j);
                    }
                    else if(currentTile->isAccepting() and gameLayout->getDFAkeys()->getCurrentState()->getkeystate()){
                        drawescape(i,j);
                    }
                    else {
                        drawTile(i,j,setting);
                    }
                }
                else{
                    setting = wall;
                    drawTile(i , j , setting);
                }
            }
        }
    }
}

void Ui_MazeWindow::EnemyMovement(){
    if(!paused){
        gameLayout->EnemyMovement();
    }
}

void Ui_MazeWindow::playergone(){
    if(gameLayout->getPlayer()->playerdead()){
        gameLayout->getPlayer()->getCurrentTile()->setStarting(false);
        MenuScreens->setCurrentWidget(gameOverScreen);
        gameLayout->getPlayer()->playerRose();
        inputTime->stop();
        enemyTime->stop();
        playerdead->stop();
    }
}


void Ui_MazeWindow::drawTile(int i, int j, tileSettings &tileType) {
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
    MazeScene->addItem(tile);
}
void Ui_MazeWindow::drawescape(int x,int y){
    QGraphicsRectItem *tile = new QGraphicsRectItem( y * nTileWidth , x * nTileHeight , nTileWidth , nTileHeight );
    tile->setBrush(QBrush( exitColor, Qt::SolidPattern));
    tile->setCacheMode(QGraphicsItem::NoCache);
    tile->setData(0, kTile );
    MazeScene->addItem(tile);
}

void Ui_MazeWindow::drawkey(int x,int y){
    QGraphicsRectItem *tile = new QGraphicsRectItem( y * nTileWidth , x * nTileHeight , nTileWidth , nTileHeight );
    tile->setBrush(QBrush( keyColor, Qt::SolidPattern));
    tile->setCacheMode(QGraphicsItem::NoCache);
    tile->setData(0, kTile );
    MazeScene->addItem(tile);
}

void Ui_MazeWindow::drawenemy(int x,int y){
    QGraphicsRectItem *tile = new QGraphicsRectItem( y * nTileWidth , x * nTileHeight , nTileWidth , nTileHeight );
    tile->setBrush(QBrush(enemyColor , Qt::SolidPattern));
    tile->setCacheMode(QGraphicsItem::NoCache);
    tile->setData(0, kTile );
    MazeScene->addItem(tile);
}
void Ui_MazeWindow::drawPlayer(int x, int y){
    QGraphicsRectItem *tile = new QGraphicsRectItem( y * nTileWidth , x * nTileHeight , nTileWidth , nTileHeight );
    tile->setBrush(QBrush(playerColor , Qt::SolidPattern));
    tile->setCacheMode(QGraphicsItem::NoCache);
    tile->setData(0, kTile );
    MazeScene->addItem(tile);
}

void Ui_MazeWindow::refreshTile(int i, int j, tileSettings &tileType) {
    int x = xFromCol(j);
    int y = yFromRow(i);
    QGraphicsItem *currentItem = MazeScene->itemAt( x , y, QTransform() );
    while (currentItem) {
        delete currentItem;
        currentItem = MazeScene->itemAt( x , y , QTransform() );
    }
    drawTile(i,j,tileType);
}

void Ui_MazeWindow::refreshPlayer(int x, int y) {
    QGraphicsItem *currentItem = MazeScene->itemAt( xFromCol(y) , yFromRow(x), QTransform() );
    while (currentItem) {
        delete currentItem;
        currentItem = MazeScene->itemAt( xFromCol(y) , yFromRow(x) , QTransform() );
    }
    drawPlayer(x,y);
}

void Ui_MazeWindow::play() {
    inputTime->start(25);
    playerdead->start(0);
    enemyTime->start(300);
}

void Ui_MazeWindow::keyPressEvent(QKeyEvent *k) {


    if(k->key() == moveUp && !paused){
        gameLayout->simulateMove(UP);
    }
    else if(k->key() == moveLeft && !paused){
        gameLayout->simulateMove(LEFT);
    }
    else if(k->key() == moveDown && !paused){
        gameLayout->simulateMove(DOWN);
    }
    else if(k->key() == moveRight && !paused){
        gameLayout->simulateMove(RIGHT);
    }
    else{
        k->ignore();
    }
}

bool Ui_MazeWindow::eventFilter(QObject *o, QEvent *e) {
    if ( e->type() == QEvent::KeyPress || e->type() == QEvent::KeyRelease ) {
        // special processing for key press
        auto *k = (QKeyEvent *)e;
        return true; // eat event
    } else {
        // standard event processing
        return false;
    }
}

void Ui_MazeWindow::fogEnabled(bool status) {
    fog = status;
}
