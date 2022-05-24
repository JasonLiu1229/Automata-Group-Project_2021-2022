#include <QtWidgets>
#include "MazeWindow.h"
#include "MazeLayout.h"

MazeWindow::MazeWindow(QWidget *parent) : QMainWindow(parent) {

    this->setBaseSize(1080,720);
    mazeLayout = new MazeLayout;
    QGraphicsView *view = new QGraphicsView(mazeLayout);
    setCentralWidget(view);
    connect(mazeLayout,SIGNAL(clicked(int,int)),this,SLOT(slot_clicked(int,int)));
    createActions();
    createMenus();
}

MazeLayout* MazeWindow::getLayout() const{
    return mazeLayout;
}

void MazeWindow::createActions() {
    newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Start a new game"));
    connect(newAct, &QAction::triggered, this, &MazeWindow::slot_newGame);

    openAct = new QAction(tr("&Open"), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Read game from disk"));
    connect(openAct, &QAction::triggered, this, &MazeWindow::slot_open);

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save game to disk"));
    connect(saveAct, &QAction::triggered, this, &MazeWindow::slot_save);

    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Abandon game"));
    connect(exitAct, &QAction::triggered, this, &MazeWindow::on_actionExit_triggered);

}

void MazeWindow::createMenus() {
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(exitAct);
}

void MazeWindow::on_actionExit_triggered() {
    if (QMessageBox::Yes == QMessageBox::question(this,
                                                  tr("Exit game"),
                                                  tr("Are you sure you want to exit the game?\nUnsaved data will be lost.")))
    {
        QApplication::quit();
    }
}

MazeWindow::~MazeWindow() {
//    delete ui;
}
