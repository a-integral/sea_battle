#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "ship.h"
#include "myfield.h"
#include "enemyfield.h"
#include "gameover_window.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

   // void on_tableWidget_cellClicked(int row, int column);

    void on_myfield_cellClicked(int row, int column);
    void on_enemyfield_cellClicked(int row, int column);

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_1deck_clicked();

    void on_radioButton_2deck_clicked();

    void on_radioButton_3deck_clicked();

    void on_radioButton_4deck_clicked();
    void on_randomput_clicked();

    void on_savebutton_clicked();
    void on_newgamebutton_clicked();

    void on_loadbutton_clicked();

private:
    Ui::MainWindow *ui;
    gameover_window gw;
    myfield myfield_obj;
    enemyfield enemyfield_obj;

};

#endif // MAINWINDOW_H
