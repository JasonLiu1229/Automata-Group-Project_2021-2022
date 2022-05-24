//
// Created by student on 24.05.22.
//
#include <QMainWindow>
#include <QMessageBox>
#include <QAction>
#include <QCloseEvent>

#ifndef AUTOMATA_GROUP_PROJECT_2021_2022_MAZEWINDOW_H
#define AUTOMATA_GROUP_PROJECT_2021_2022_MAZEWINDOW_H

//namespace  Ui {
//    class MazeWindow;
//}

class MazeWindow : public QMainWindow {

    Q_OBJECT

public:
    MazeWindow(QWidget *parent = nullptr);

    virtual  ~MazeWindow();

    virtual void update()=0;

private://    virtual void clicked(int x, int y)=0;
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
//    void slot_undo() {undo();}
//    void slot_redo() {redo();}
//    void slot_visualizationChange() {visualizationChange();}


    void on_actionExit_triggered();
    void closeEvent (QCloseEvent *event)
    {
        on_actionExit_triggered();
        event->ignore();
    }

private:
    void createActions();
    void createMenus();
    QMenu *fileMenu;
//    QMenu *gameMenu;
//    QMenu *visualizeMenu;

    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *exitAct;

//    Ui::MazeWindow *ui;
};

#endif //AUTOMATA_GROUP_PROJECT_2021_2022_MAZEWINDOW_H
