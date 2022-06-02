#include <iostream>
#include <qmainwindow.h>
#include <QtWidgets>
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

    // Create actions
    createActions(MainWindow);
    // Create menus
    createMenus(MainWindow);
    // Retranslate
    retranslateUi(MainWindow);
    paused = false;
    this->grabKeyboard();
//    this->installEventFilter(this);
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
    actionFullscreen->setText(QApplication::translate("MainWindow", "Fullscreen", nullptr));
    actionFullscreen->setShortcut(QApplication::translate("MainWindow", "Ctrl+F", nullptr));
    actionGame_Options->setText(QApplication::translate("MainWindow", "Game Options", nullptr));
    newGameButton->setText(QApplication::translate("MainWindow", "New Game", nullptr));
    LoadGameButton->setText(QApplication::translate("MainWindow", "Load Game", nullptr));
    OptionsButton->setText(QApplication::translate("MainWindow", "Options", nullptr));
    ExitButton->setText(QApplication::translate("MainWindow", "Exit", nullptr));
    menuFile->setTitle(QApplication::translate("MainWindow", "File", nullptr));
    menuOptions->setTitle(QApplication::translate("MainWindow", "Options", nullptr));

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

    MenuScreens->addWidget(LevelSelectionScreen);
    MenuScreens->addWidget(levelScreen);
    MenuScreens->addWidget(optionsScreen);

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
    MainWindow->setStatusBar(statusbar);

    menubar->addAction(menuFile->menuAction());
    menubar->addAction(menuOptions->menuAction());
    menuFile->addAction(loadAct);
    menuFile->addAction(saveAct);
    menuFile->addAction(exitAct);
    menuOptions->addAction(actionFullscreen);
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

    wallColorLineEdit = new QLineEdit(VisualisationOptionsBox);
    wallColorLineEdit->setObjectName(QString::fromUtf8("wallColorLineEdit"));

    formLayout_3->setWidget(0, QFormLayout::FieldRole, wallColorLineEdit);

    pathColorLabel = new QLabel(VisualisationOptionsBox);
    pathColorLabel->setObjectName(QString::fromUtf8("pathColorLabel"));

    formLayout_3->setWidget(1, QFormLayout::LabelRole, pathColorLabel);

    pathColorLineEdit = new QLineEdit(VisualisationOptionsBox);
    pathColorLineEdit->setObjectName(QString::fromUtf8("pathColorLineEdit"));

    formLayout_3->setWidget(1, QFormLayout::FieldRole, pathColorLineEdit);

    playerColorLabel = new QLabel(VisualisationOptionsBox);
    playerColorLabel->setObjectName(QString::fromUtf8("playerColorLabel"));

    formLayout_3->setWidget(2, QFormLayout::LabelRole, playerColorLabel);

    playerColorLineEdit = new QLineEdit(VisualisationOptionsBox);
    playerColorLineEdit->setObjectName(QString::fromUtf8("playerColorLineEdit"));

    formLayout_3->setWidget(2, QFormLayout::FieldRole, playerColorLineEdit);

    enemyColorLabel = new QLabel(VisualisationOptionsBox);
    enemyColorLabel->setObjectName(QString::fromUtf8("enemyColorLabel"));

    formLayout_3->setWidget(3, QFormLayout::LabelRole, enemyColorLabel);

    enemyColorLineEdit = new QLineEdit(VisualisationOptionsBox);
    enemyColorLineEdit->setObjectName(QString::fromUtf8("enemyColorLineEdit"));

    formLayout_3->setWidget(3, QFormLayout::FieldRole, enemyColorLineEdit);

    keyColorLabel = new QLabel(VisualisationOptionsBox);
    keyColorLabel->setObjectName(QString::fromUtf8("keyColorLabel"));

    formLayout_3->setWidget(4, QFormLayout::LabelRole, keyColorLabel);

    keyColorLineEdit = new QLineEdit(VisualisationOptionsBox);
    keyColorLineEdit->setObjectName(QString::fromUtf8("keyColorLineEdit"));

    formLayout_3->setWidget(4, QFormLayout::FieldRole, keyColorLineEdit);

    exitColorLabel = new QLabel(VisualisationOptionsBox);
    exitColorLabel->setObjectName(QString::fromUtf8("exitColorLabel"));

    formLayout_3->setWidget(5, QFormLayout::LabelRole, exitColorLabel);

    exitColorLineEdit = new QLineEdit(VisualisationOptionsBox);
    exitColorLineEdit->setObjectName(QString::fromUtf8("exitColorLineEdit"));

    formLayout_3->setWidget(5, QFormLayout::FieldRole, exitColorLineEdit);


    gridLayout_2->addWidget(VisualisationOptionsBox, 1, 0, 1, 1);

    KeybindsBox = new QGroupBox(optionsScreen);
    KeybindsBox->setObjectName(QString::fromUtf8("KeybindsBox"));
    formLayout_4 = new QFormLayout(KeybindsBox);
    formLayout_4->setObjectName(QString::fromUtf8("formLayout_4"));
    formLayout_4->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
    moveUpLabel = new QLabel(KeybindsBox);
    moveUpLabel->setObjectName(QString::fromUtf8("moveUpLabel"));

    formLayout_4->setWidget(0, QFormLayout::LabelRole, moveUpLabel);

    moveUpLineEdit = new QLineEdit(KeybindsBox);
    moveUpLineEdit->setObjectName(QString::fromUtf8("moveUpLineEdit"));

    formLayout_4->setWidget(0, QFormLayout::FieldRole, moveUpLineEdit);

    moveDownLabel = new QLabel(KeybindsBox);
    moveDownLabel->setObjectName(QString::fromUtf8("moveDownLabel"));

    formLayout_4->setWidget(1, QFormLayout::LabelRole, moveDownLabel);

    moveDownLineEdit = new QLineEdit(KeybindsBox);
    moveDownLineEdit->setObjectName(QString::fromUtf8("moveDownLineEdit"));

    formLayout_4->setWidget(1, QFormLayout::FieldRole, moveDownLineEdit);

    moveLeftLabel = new QLabel(KeybindsBox);
    moveLeftLabel->setObjectName(QString::fromUtf8("moveLeftLabel"));

    formLayout_4->setWidget(2, QFormLayout::LabelRole, moveLeftLabel);

    moveLeftLineEdit = new QLineEdit(KeybindsBox);
    moveLeftLineEdit->setObjectName(QString::fromUtf8("moveLeftLineEdit"));

    formLayout_4->setWidget(2, QFormLayout::FieldRole, moveLeftLineEdit);

    moveRightLabel = new QLabel(KeybindsBox);
    moveRightLabel->setObjectName(QString::fromUtf8("moveRightLabel"));

    formLayout_4->setWidget(3, QFormLayout::LabelRole, moveRightLabel);

    moveRightLineEdit = new QLineEdit(KeybindsBox);
    moveRightLineEdit->setObjectName(QString::fromUtf8("moveRightLineEdit"));

    formLayout_4->setWidget(3, QFormLayout::FieldRole, moveRightLineEdit);


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
    mainMenuButton_optionsScreen->setText(QApplication::translate("OptionsScreen", "Main Menu", nullptr));

    // Connect buttons to slots
    connect(mainMenuButton_optionsScreen , SIGNAL(clicked()) , this , SLOT(slot_mainMenu()) );

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
//        gameLayout->saveGame();
    }
}

void Ui_MazeWindow::load() {
    cout << "Load Game option" << endl;
}

void Ui_MazeWindow::options() {
    MenuScreens->setCurrentWidget(optionsScreen);
}

void Ui_MazeWindow::mainMenuReturn() {
    MenuScreens->setCurrentWidget(MainScreen);
}

void Ui_MazeWindow::loadLevel(string filename){
    // Initialize parser
    Parser* parser = new Parser(filename);
    // Create maze
    gameLayout = new Maze();
    // Load maze
    gameLayout->loadGame(LEVDIR + parser->getTxt_Filename());
//    gameLayout->setLevelName(parser->getTxt_Filename());

    MenuScreens->setCurrentWidget(levelScreen);
    // Create Graphics Scene
    MazeScene = new QGraphicsScene(MazeView);
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    // Set parameters
    nTileWidth = kWidth;
    nTileHeight = kWidth;
    nBorderWidth = 0;
    nBorderHeight = 0;
    wallColor = Qt::black;
    pathColor = Qt::gray;
    exitColor = QColor(150,75,0);
    playerColor = Qt::white;
    enemyColor = QColor(138,3,3);

    // Draw the maze(make all the tiles)
    update();
    // Set the scene
    MazeView->setScene(MazeScene);
    // Change the window view
    delete parser;
    inputTime = new QTimer;
    connect(inputTime, &QTimer::timeout, this, QOverload<>::of(&Ui_MazeWindow::update));
    inputTime->start(0);
    MazeView->setFocus();
    cout << "Loaded level " + filename << endl;

}
void Ui_MazeWindow::pauseGame() {
    cout << "Pause Game option" << endl;
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
    refreshMaze(gameLayout);
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
            if(currentTile->isStarting()) {
                drawPlayer(i , j);
            }
            else {
                drawTile(i,j,setting);
            }
        }
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

}

void Ui_MazeWindow::keyPressEvent(QKeyEvent *k) {

    if(k->key() == Qt::Key_W || k->key() == Qt::Key_Up){
        gameLayout->simulateMove(UP);
    }
    else if(k->key() == Qt::Key_A || k->key() == Qt::Key_Left){
        gameLayout->simulateMove(LEFT);
    }
    else if(k->key() == Qt::Key_S || k->key() == Qt::Key_Down){
        gameLayout->simulateMove(DOWN);
    }
    else if(k->key() == Qt::Key_D || k->key() == Qt::Key_Right){
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

