#include "battlefield.h"
#include <iostream>
using namespace std;

battlefield::battlefield(){
    this->currentstate=10;
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++)
           {
                this->field[i][j]=0;
           }
    hor_state=1;
    cout<<"constructor"<<endl;
    for(int i=0;i<4;i++)
    {
        freeships[i]=1+i;//нулевой - четырехпалубник: одна штука
    }
    shipsalive=10;
    shiptype=4;
}
bool battlefield::validpos(int x,int y){
    return x<10 && x>-1 && y<10 && y>-1;
}


int battlefield::checkplacement(int x,int y,int n,int hor)
{
    if (hor&&(x+n>10)) return 1;
    if (!hor&&(y+n>10)) return 1;
    if (hor) //проверяем соседние с кораблем позиции
        {
            for (int i=-1;i<=n;i++)
            {
                if (validpos(x+i,y-1)) //если соседняя позиция за пределами поля, проверять не надо
                {
                    if (field[x+i][y-1]) return 1;
                }
                if (validpos(x+i,y+1))
                {
                    if (field[x+i][y+1]) return 1;
                }
            }
            if (validpos(x-1,y))
            {
                if (field[x-1][y]) return 1;
            }
            if (validpos(x+n,y))
            {
                if (field[x+n][y]) return 1;
            }
            for (int i=0;i<n;i++)
                if (field[x+i][y]) return 1;// проверка на месте установки корабля
        }
    else
    {
        for (int i=-1;i<=n;i++)
        {
            if (validpos(x-1,y+i)) //если соседняя позиция за пределами поля, проверять не надо
            {
                if (field[x-1][y+i]) return 1;
            }
            if (validpos(x+1,y+i))
            {
                if (field[x+1][y+i]) return 1;
            }
        }

        if (validpos(x,y-1))
        {
            if (field[x][y-1]) return 1;
        }
        if (validpos(x,y+n))
        {
            if (field[x][y+n]) return 1;
        }
        for (int i=0;i<n;i++)
            if (field[x][y+i]) return 1;// проверка на месте установки корабля
    }
    return 0;
}


















