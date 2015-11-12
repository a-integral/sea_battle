#ifndef BATTLEFIELD
#define BATTLEFIELD
#include "ship.h"
#include "QObject"
#include <QTableWidget>
#include "ui_mainwindow.h"
#include <iostream>
using namespace std;
class battlefield
{
protected:
    int currentstate;//какой по счету корабль ставим (от 10 до 1,0-расстановка закончена)
    int freeships[4];//для контроля за расстановкой кораблей по правилам (1 4х пал.,2 3х пал.)
    int shiptype;//текущий устанавливаемый корабль

    int checkplacement(int x,int y,int n,int hor);
    ship ships[10];
    bool validpos(int x, int y);
    int hor_state;
 public:
    int shipsalive;
    int field[10][10];
    //virtual void ai_placement()=0;
    battlefield();
    //virtual ~battlefield(){};
    void sethor(){hor_state=1;cout<<"hor_state=1"<<endl;}
    void setvert(){hor_state=0;cout<<"hor_state=0"<<endl;}
    void setfourdeck(){shiptype=4;}
    void setthreedeck(){shiptype=3;}
    void settwodeck(){shiptype=2;}
    void setonedeck(){shiptype=1;}
    bool ready(){if (currentstate==0&&shipsalive!=0) return true;else return false;}
    QTableWidget * dadui;  
    Ui::MainWindow * gui;
    virtual int put(int x,int y)=0;
    virtual int strike(int x,int y)=0;
    virtual void save()=0;
    virtual void resetfield()=0;
    virtual void load()=0;
private slots:
    void on_enemyfield_clicked(const QModelIndex &index);
    void on_myfield_cellClicked(int row, int column);
    void on_enemyfield_cellClicked(int row, int column);
};

#endif // BATTLEFIELD

