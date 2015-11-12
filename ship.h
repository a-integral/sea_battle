#ifndef SHIP_H
#define SHIP_H
#include <iostream>
#include <fstream>
using namespace std;
class ship
{
    int deck[4];//1,0,-1 палуба присутствует/отсутствует/подбита
    int num,alive;
    int x,y,hor;//координаты начала корабля, кол-во палуб, положение
public:
    int getx(){return x;}
    int gety(){return y;}
    int getn(){return num;}
    int gethor(){return hor;}
    int getdeck(int x_coord,int y_coord);
    ship(int n,int x_coord,int y_coord,int hor_pos);
    ship();
    int strikeship(int x,int y);
    friend ostream & operator<<(ostream & stream,ship & o);
    friend istream & operator>>(istream & stream,ship & o);
};

#endif // SHIP_H
