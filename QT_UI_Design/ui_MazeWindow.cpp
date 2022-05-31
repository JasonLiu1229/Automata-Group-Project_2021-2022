#include <iostream>
#include "ui_MazeWindow.h"

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

    retranslateUi(MainWindow);



} // setupUi

void Ui_MazeWindow::retranslateUi(QMainWindow *MainWindow)
{
    MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Untitled Maze Game", nullptr));

#ifndef QT_NO_ACCESSIBILITY
    MainWindow->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY

    openAct->setText(QApplication::translate("MainWindow", "Open", nullptr));
    saveAct->setText(QApplication::translate("MainWindow", "Save", nullptr));
    exitAct->setText(QApplication::translate("MainWindow", "Exit", nullptr));
    actionFullscreen->setText(QApplication::translate("MainWindow", "Fullscreen", nullptr));
    actionFullscreen->setShortcut(QApplication::translate("MainWindow", "Ctrl+F", nullptr));
    actionGame_Options->setText(QApplication::translate("MainWindow", "Game Options", nullptr));
    actionWindow_Options->setText(QApplication::translate("MainWindow", "Window Options", nullptr));
    newGameButton->setText(QApplication::translate("MainWindow", "New Game", nullptr));
    LoadGameButton->setText(QApplication::translate("MainWindow", "Load Game", nullptr));
    OptionsButton->setText(QApplication::translate("MainWindow", "Options", nullptr));
    ExitButton->setText(QApplication::translate("MainWindow", "Exit", nullptr));
    menuFile->setTitle(QApplication::translate("MainWindow", "File", nullptr));
    menuOptions->setTitle(QApplication::translate("MainWindow", "Options", nullptr));

}

void Ui_MazeWindow::createActions(QMainWindow *MainWindow) {

    openAct = new QAction(tr("&Open"), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Read game from disk"));
    connect(openAct, &QAction::triggered, this, &Ui_MazeWindow::slot_open);

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

    actionWindow_Options = new QAction(MainWindow);
    actionWindow_Options->setObjectName(QString::fromUtf8("actionWindow_Options"));

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

    createSelectionScreen(MainWindow);
    MenuScreens->addWidget(LevelSelectionScreen);

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
    menuFile->addAction(openAct);
    menuFile->addAction(saveAct);
    menuFile->addAction(exitAct);
    menuOptions->addAction(actionFullscreen);
    menuOptions->addAction(actionGame_Options);
    menuOptions->addAction(actionWindow_Options);

}

void Ui_MazeWindow::on_actionExit_triggered() {
    if (QMessageBox::Yes == QMessageBox::question(this,
                                                  tr("Exit game"),
                                                  tr("Are you sure you want to exit the game?\nUnsaved data will be lost.")))
    {
        QApplication::quit();
    }
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
    connect(MenuButton, SIGNAL(clicked()), this, SLOT( slot_mainMenu() ) );

    LevelsGrid->addWidget(Level1, 0, 0, 1, 1);
    LevelsGrid->addWidget(Level2, 0, 1, 1, 1);
    LevelsGrid->addWidget(Level3, 1, 0, 1, 1);
    LevelsGrid->addWidget(Level4, 1, 1, 1, 1);


    Level3->setText(QApplication::translate("MainWindow", "Level 3", nullptr));
    Level4->setText(QApplication::translate("MainWindow", "Level 4", nullptr));
    Level1->setText(QApplication::translate("MainWindow", "Level 1", nullptr));
    Level2->setText(QApplication::translate("MainWindow", "Level 2", nullptr));

    MenuButton->setText(QApplication::translate("MainWindow", "Main menu", nullptr));

}

void Ui_MazeWindow::on_actionOptions_triggered() {

}

void Ui_MazeWindow::newGame() {
    MenuScreens->setCurrentWidget(LevelSelectionScreen);
}

void Ui_MazeWindow::open() {
    cout << "Open Game option" << endl;
}

void Ui_MazeWindow::save() {
    cout << "Save Game option" << endl;
}

void Ui_MazeWindow::load() {
    cout << "Load Game option" << endl;
}

void Ui_MazeWindow::options() {
    cout << "Options option" << endl;
}

void Ui_MazeWindow::mainMenuReturn() {
    MenuScreens->setCurrentWidget(MainScreen);
}
