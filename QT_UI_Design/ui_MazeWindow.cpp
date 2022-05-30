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
    connect(actionFullscreen , &QAction::triggered , this, &Ui_MazeWindow::slot_fullscreen);

    actionGame_Options = new QAction(MainWindow);
    actionGame_Options->setObjectName(QString::fromUtf8("actionGame_Options"));

    actionWindow_Options = new QAction(MainWindow);
    actionWindow_Options->setObjectName(QString::fromUtf8("actionWindow_Options"));

}

void Ui_MazeWindow::createMenus(QMainWindow *MainWindow) {

    // Size policy
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);

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
    QPushButton::connect(ExitButton, SIGNAL(clicked()), this, SLOT(on_actionExit_triggered()));


    MainScreenLayout->addWidget(newGameButton);
    MainScreenLayout->addWidget(LoadGameButton);
    MainScreenLayout->addWidget(OptionsButton);
    MainScreenLayout->addWidget(ExitButton);

    MainWindow->setCentralWidget(MainScreen);

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

void Ui_MazeWindow::on_actionOptions_triggered() {

}

void Ui_MazeWindow::newGame() {
    cout << "New Game option" << endl;
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
