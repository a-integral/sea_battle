#include "ship.h"
#include <iostream>
using namespace std;
ship::ship(int n,int x_coord,int y_coord,int hor_pos)
{
    alive=num=n;

    for (int i=0;i<n;i++)
    {
        deck[i]=1;
    }
    for (int i=n;i<4;i++)
    {
        deck[i]=0;
    }
    x=x_coord;
    y=y_coord;
    hor=hor_pos;
}
ostream & operator<<(ostream&stream,ship & o)
{
    cout<<"save ships\n";
    for (int i=0;i<4;i++) stream<<o.deck[i]<<endl;
    stream<<o.num<<endl<<o.alive<<endl<<o.x<<endl<<o.y<<endl<<o.hor<<endl;
    return stream;
}
istream & operator>>(istream&stream,ship & o)
{
    cout<<"load ships\n";
    for (int i=0;i<4;i++) stream>>o.deck[i];
    stream>>o.num>>o.alive>>o.x>>o.y>>o.hor;
    return stream;
}
ship::ship(){};

int ship::strikeship(int x_coord,int y_coord)
{
    if (!alive) return -1;//бъем по уже убитому
    int strikedeck;
    if (hor)
    {
        strikedeck=x_coord-x;
    }
    else
    {
        strikedeck=y_coord-y;
    }
    if (deck[strikedeck]==-1)
    {
        return -1; //бъем по палубе,куда уже били
    }
    else
    {
        deck[strikedeck]=-1;
        alive--;
        if (alive) return 1; //ранил
        return 2;//убил
    }
}
int ship::getdeck(int x_coord,int y_coord)
{
    if (hor)
    {
        return(deck[x_coord-x]);
    }
    else
    {
        return(deck[y_coord-y]);
    }
}
