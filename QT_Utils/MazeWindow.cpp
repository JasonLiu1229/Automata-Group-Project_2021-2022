#include <QtWidgets>
#include <QInputDialog>
#include <QColorDialog>
#include <QDialogButtonBox>
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>
#include "MazeWindow.h"
#include "MazeLayout.h"

MazeWindow::MazeWindow(QWidget *parent) : QMainWindow(parent) {

    this->resize(1280,720); // 720p HD
    this->setMinimumSize(426,240); // 240p
    this->setMaximumSize(1920,1080); // 1080p Full HD
    mazeLayout = new MazeLayout;
    QGraphicsView *layoutDisplay = new QGraphicsView(mazeLayout);
    setCentralWidget(layoutDisplay);
    //    view->setBaseSize(1080,720);
    //volgende lijn moet aangepast worden in functie van ingedrukte toetsen ipv clicks
    connect(mazeLayout,SIGNAL(clicked(int,int)),this,SLOT(slot_clicked(int,int)));
    createActions();
    createMenus();
}

MazeLayout* MazeWindow::getLayout() const{
    return mazeLayout;
}

void MazeWindow::createActions() {
    // File menu actions
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
    // Option menu action
    options = new QAction(tr("&options") , this);
    options->setStatusTip(tr("Options"));
    connect(options,&QAction::triggered,this, &MazeWindow::on_actionOptions_triggered);
}

void MazeWindow::createMenus() {
    // Add file menu
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(exitAct);
    // Add options menu
    optionsMenu = menuBar()->addMenu(tr("&options"));
    optionsMenu->addAction(options);
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

OptionsWidget::OptionsWidget(QWidget *parent) : QDialog(parent) {
    // Create new form
    QFormLayout *lytMain = new QFormLayout(this);
    // Get width
    QLabel *w_label = new QLabel(QString("Width: ").arg(0), this);
    QLineEdit *w_line = new QLineEdit(this);
    lytMain->addRow(w_label, w_line);
    fields << w_line;
    // Get height
    QLabel *h_label = new QLabel(QString("Width: ").arg(1), this);
    QLineEdit *h_line = new QLineEdit(this);
    lytMain->addRow(h_label, h_line);
    fields << h_line;
    // Confirm and cancel field
    QDialogButtonBox *buttonBox = new QDialogButtonBox
            ( QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
              Qt::Horizontal, this );
    lytMain->addWidget(buttonBox);

    bool conn = connect(buttonBox, &QDialogButtonBox::accepted,
                        this, &OptionsWidget::accept);
    Q_ASSERT(conn);
    conn = connect(buttonBox, &QDialogButtonBox::rejected,
                   this, &OptionsWidget::reject);
    Q_ASSERT(conn);
    setLayout(lytMain);
}

QStringList OptionsWidget::getStrings(QWidget *parent, bool *ok) {
    OptionsWidget *dialog = new OptionsWidget(parent);

    QStringList list;

    const int ret = dialog->exec();
    if (ok)
        *ok = ret != 0;

    if (ret) {
                foreach (auto field, dialog->fields) {
                list << field->text();
            }
    }

    dialog->deleteLater();

    return list;
}
