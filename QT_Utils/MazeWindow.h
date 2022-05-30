#include <QMainWindow>
#include <QMessageBox>
#include <QAction>
#include <QCloseEvent>

#ifndef AUTOMATA_GROUP_PROJECT_2021_2022_MAZEWINDOW_H
#define AUTOMATA_GROUP_PROJECT_2021_2022_MAZEWINDOW_H

class QGraphicsScene;
class QLineEdit;
class QLabel;
class MazeLayout;

class OptionsWidget : public QDialog {
    Q_OBJECT
public:
    explicit OptionsWidget(QWidget *parent = nullptr);

    static QStringList getStrings(QWidget *parent, bool *ok = nullptr);

private:
    QList<QLineEdit*> fields;
};


class MazeWindow : public QMainWindow {

    Q_OBJECT

public:
    MazeWindow(QWidget *parent = nullptr);

    virtual  ~MazeWindow();

    virtual void update()=0;

    MazeLayout* getLayout() const;

private:
//    virtual void clicked(int x, int y)=0;
    virtual void newGame()=0;
    virtual void open() =0;
    virtual void save()=0;
//    virtual void undo()=0;
//    virtual void redo()=0;
//    virtual void visualizationChange()=0;


private slots:
//    void slot_clicked(int x, int y) {clicked(x,y);}
    void slot_newGame() {newGame();}
    void slot_open() {open();}
    void slot_save() {save();}
//    void slot_visualizationChange() {visualizationChange();}


    void on_actionExit_triggered();
    virtual void on_actionOptions_triggered() = 0;
    void closeEvent (QCloseEvent *event)
    {
        on_actionExit_triggered();
        event->ignore();
    }

private:
    void createActions();
    void createMenus();
    MazeLayout* mazeLayout;
    // Menus
    QMenu *fileMenu;
    QMenu *optionsMenu;
    // File menu options
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *exitAct;
    // Options menu options
    QAction *options;

};

#endif //AUTOMATA_GROUP_PROJECT_2021_2022_MAZEWINDOW_H
