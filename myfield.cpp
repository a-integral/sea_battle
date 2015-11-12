#include "myfield.h"
#include "myfield.h"
#include <iostream>
#include "qthread.h"
#include "QAbstractTableModel"
#include "QAbstractItemModel"
using namespace std;
myfield::myfield()
{

}
myfield::~myfield()
{
    cout<<"destroyed!"<<endl;
}

int myfield::strike(int x,int y)
{
    /*if (!validpos(x,y)) return -1;
    if (!field[x][y])
    {
        field[x][y]=-1;
        return 0;//не попали
    }
    if (field[x][y]==-1) return -1;//уже били
    int id=field[x][y];
    int hit = ships[id].strikeship(x,y);
    */
    int hit;
    if (!validpos(x,y)) return -1;
    if (field[x][y]==-1) return -1;//уже били по пустому
    if (!field[x][y])
    {
        field[x][y]=-1;//отмечаем в поле что били по пустому
        hit=0;//не попали
    }
    int id=field[x][y];
    if (id>0)
    {
        hit = ships[id-1].strikeship(x,y); //атакуем палубу, узнаем результат
        cout<<"result"<<hit<<endl;
    }
    if (hit==-1) return -1;//уже били эту палубу
    //работа с интерфейсом
    if (hit==0)
    {
        QTableWidgetItem * ti=gui->myfield->item(y,x);
        if(!ti){
            ti=new QTableWidgetItem();
        }
        gui->myfield->setItem(y,x,ti);
        blink(x,y);
        ti->setText("-");
        cout<<"hit0"<<endl;
        cout<<x<<y<<endl;
    }
    if (hit==1)
    {
        cout<<"hit1"<<endl;
         cout<<x<<y<<endl;
       blink(x,y);
       gui->myfield->item(y,x)->setText("X");
       gui->myfield->item(y,x)->setBackgroundColor(QColor(255,100,100));
    }
    if (hit==2)
    {

       cout<<"hit2"<<endl;
        cout<<x<<y<<endl;
       int nship=ships[id-1].getn();
       int xship=ships[id-1].getx();
       int yship=ships[id-1].gety();
       int horship=ships[id-1].gethor();
       shipsalive--;
       //gui->myfield->item(y,x)->setText("X");
        cout<<nship<<xship<<yship<<horship<<endl;
       if(horship)
       {
           for (int i=xship-1;i<=xship+nship;i++)
           {
               if (validpos(i,yship-1))
               {
                   field[i][yship-1]=-1;
                   QTableWidgetItem * ti=gui->myfield->item(yship-1,i);
                   if(!ti){
                       ti=new QTableWidgetItem();
                        gui->myfield->setItem(yship-1,i,ti);
                   }
                   gui->myfield->item(yship-1,i)->setText("-");

               }//проставим "-" сверху
               if (validpos(i,y+1))
               {
                    field[i][yship+1]=-1;
                   QTableWidgetItem * ti=gui->myfield->item(yship+1,i);
                   if(!ti){
                       ti=new QTableWidgetItem();
                       gui->myfield->setItem(yship+1,i,ti);
                   }

                   gui->myfield->item(yship+1,i)->setText("-");//проставим "-" снизу
               }
           }
           if (validpos(xship-1,yship))
           {
                field[xship-1][y]=-1;
               QTableWidgetItem * ti=gui->myfield->item(yship,xship-1);
               if(!ti){
                   ti=new QTableWidgetItem();
                   gui->myfield->setItem(yship,xship-1,ti);
               }
                gui->myfield->item(yship,xship-1)->setText("-");

           }//слева
           if (validpos(xship+nship,yship))
           {
               field[xship+nship][y]=-1;
               QTableWidgetItem * ti=gui->myfield->item(yship,xship+nship);
               if(!ti){
                   ti=new QTableWidgetItem();
                   gui->myfield->setItem(yship,xship+nship,ti);
               }
               gui->myfield->item(yship,xship+nship)->setText("-");
           }//справа
       }
       else
       {
           for (int i=yship-1;i<=yship+nship;i++)
           {
               if (validpos(xship-1,i))
               {
                   field[xship-1][i]=-1;
                   QTableWidgetItem * ti=gui->myfield->item(i,xship-1);
                   if(!ti){
                       ti=new QTableWidgetItem();
                       gui->myfield->setItem(i,xship-1,ti);
                   }
                   gui->myfield->item(i,xship-1)->setText("-");
                  ;
               }//проставим "-" слева
               if (validpos(xship+1,i))
               {
                   field[xship+1][i]=-1;
                   QTableWidgetItem * ti=gui->myfield->item(i,xship+1);
                   if(!ti){
                       ti=new QTableWidgetItem();
                       gui->myfield->setItem(i,xship+1,ti);
                   }
                   gui->myfield->item(i,xship+1)->setText("-");
                 //проставим "-" справа
               }
           }
           if (validpos(xship,yship-1))
           {
               field[xship][yship-1]=-1;
               QTableWidgetItem * ti=gui->myfield->item(yship-1,xship);
               if(!ti){
                   ti=new QTableWidgetItem();
                   gui->myfield->setItem(yship-1,xship,ti);
               }
               gui->myfield->item(yship-1,xship)->setText("-");
           }//сверху
           if (validpos(xship,yship+nship))
           {
               field[xship][yship+1]=-1;
               QTableWidgetItem * ti=gui->myfield->item(yship+nship,xship);
               if(!ti){
                   ti=new QTableWidgetItem();
                   gui->myfield->setItem(yship+nship,xship,ti);
               }
               gui->myfield->item(yship+nship,xship)->setText("-");
           }//снизу
       }
       blink(x,y);
       gui->myfield->item(y,x)->setBackgroundColor(QColor(255,0,0));
    }
    return hit;
}

void myfield::ai_placement()
{
    int status;
    do
   {
        int x=rand()%10;
        int y=rand()%10;
        if(rand()%2)
        {
            setvert();
        }
        else
        {
            sethor();
        }
        status=put(x,y);
        if (status==-2) shiptype--;
    }
    while(status);
}

int myfield::put(int x, int y)
{
        int n=shiptype;
        if (this->currentstate==0) return -1; //расстановка закончена
        if (freeships[4-shiptype]==0) return -2;//корабли этого типа закончились
           int id=currentstate;
           if (checkplacement(x,y,n,hor_state)) return -1; //можно ли поставить туда корабль , 1- нельзя
           cout<<hor_state<<endl;
           if (!hor_state)
           {
               cout<<"vert"<<endl;
                cout<<hor_state<<endl;
               for (int i=0;i<n;i++)
               {
                   field[x][y+i]=id;//записываем в поле идентификатор корабля

               //cout<<"point"<<endl;
               //QTableWidgetItem * ti=daduig->item(y+i,x);
                   QTableWidgetItem * ti=gui->myfield->item(y+i,x);
               //cout<<ti<<endl;
                 if(!ti){
                   ti=new QTableWidgetItem();
                   gui->myfield->setItem(y+i,x,ti);
                   //cout<<"created"<<endl;
                 }

               //cout<<"setting"<<endl;
               ti->setBackgroundColor(QColor(255,255,0));
               ti->setText("X");
               //cout<<"setted"<<endl;
               }

           }
           if (hor_state)
           {
               cout<<"hor"<<endl;
               cout<<hor_state<<endl;
               for(int i=0;i<n;i++){
                   field[x+i][y]=id;
                   //cout<<"point"<<endl;
                   QTableWidgetItem * ti=gui->myfield->item(y,x+i);
                   cout<<ti<<endl;
                   if(!ti){
                       ti=new QTableWidgetItem();
                       gui->myfield->setItem(y,x+i,ti);
                       //cout<<"created"<<endl;
                   }
                   //cout<<"setting"<<endl;
                   ti->setBackgroundColor(QColor(255,255,0));
                   ti->setText("X");
                   //cout<<"setted"<<endl;
               }

           }

           cout<<hor_state<<endl;
           ship temp(n,x,y,hor_state);
           this->ships[id-1]=temp;
           this->currentstate--;
           this->freeships[4-shiptype]--;
           if (this->currentstate==0)
           {
               gui->gui_decknum->setEnabled(false);
               gui->gui_shippos->setEnabled(false);
               return 0;
           }
           return 1;
           cout<<"______________"<<endl;
}

void myfield::blink(int x,int y)
{
    QThread t1;
   // gui->myfield->item(y,x)->setBackgroundColor(QColor(0,0,0));
    gui->myfield->item(y,x)->setBackground(QBrush(QColor(0,0,0)));
    //QModelIndex ind=gui->myfield->model()->index(y,x);
    //gui->myfield->model()->dataChanged(ind,ind);
    gui->myfield->repaint();
    t1.msleep(300);
    //gui->myfield->item(y,x)->setBackgroundColor(QColor(255,255,255));
    gui->myfield->item(y,x)->setBackground(QBrush(QColor(255,255,255)));
    gui->myfield->repaint();
    t1.msleep(300);
    //gui->myfield->item(y,x)->setBackgroundColor(QColor(0,0,0));
    gui->myfield->item(y,x)->setBackground(QBrush(QColor(0,0,0)));
    gui->myfield->repaint();
    t1.msleep(300);
    //gui->myfield->item(y,x)->setBackgroundColor(QColor(255,255,255));
    gui->myfield->item(y,x)->setBackground(QBrush(QColor(255,255,255)));
    gui->myfield->repaint();
}

ostream & operator<<(ostream&stream,myfield & o)
{
    cout<<"save myfield\n";
    stream<<o.currentstate<<endl;
    for (int i=0;i<4;i++) stream<<o.freeships[i]<<endl;
    stream<<o.shiptype<<endl<<o.shipsalive<<endl;
    for (int i=0;i<10;i++) stream<<o.ships[i];
    stream<<o.hor_state<<endl;
    for (int i=0;i<10;i++)
        for (int j=0;j<10;j++)
            stream<<o.field[j][i]<<endl;
    return stream;
}
void myfield::save()
{
    ofstream out("myfield.dat",ios::out);
    out<<*this;
}
istream & operator>>(istream&stream,myfield & o)
{
    cout<<"load myfield\n";
    stream>>o.currentstate;
    for (int i=0;i<4;i++) stream>>o.freeships[i];
    stream>>o.shiptype>>o.shipsalive;
    for (int i=0;i<10;i++) stream>>o.ships[i];
    stream>>o.hor_state;
    for (int i=0;i<10;i++)
        for (int j=0;j<10;j++)
            stream>>o.field[j][i];
    return stream;
}
void myfield::load()
{
    this->resetfield();
    ifstream in("myfield.dat",ios::in);
    in>>*this;
    //перерисовываем интерфейс
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++)
        {
            int x=j;
            int y=i;
            if (field[j][i]==-1)
            {
                QTableWidgetItem * ti=gui->myfield->item(y,x);
                if(!ti){
                    ti=new QTableWidgetItem();
                }
                gui->myfield->setItem(y,x,ti);
                ti->setText("-");
            }
            if (field[j][i]>0)
            {
                int deckstate=ships[field[j][i]-1].getdeck(j,i);
                if (deckstate==1)
                {
                    QTableWidgetItem * ti=gui->myfield->item(y,x);
                    if(!ti)
                    {
                        ti=new QTableWidgetItem();
                        gui->myfield->setItem(y,x,ti);
                    }
                    ti->setBackgroundColor(QColor(255,255,0));
                    ti->setText("X");
                }
                if (deckstate==-1)
                {
                    QTableWidgetItem * ti=gui->myfield->item(y,x);
                    if(!ti)
                    {
                        ti=new QTableWidgetItem();
                        gui->myfield->setItem(y,x,ti);
                    }
                    gui->myfield->item(y,x)->setText("X");
                    gui->myfield->item(y,x)->setBackgroundColor(QColor(255,100,100));
                }

            }
        }
}

void myfield::resetfield()
{
    //сбросим все переменные статуса поля на начальные
    //компилятор не дает возможность вызвать конструктор
    this->currentstate=10;
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++)
           {
                this->field[i][j]=0;
           }
    hor_state=1;
    cout<<"reset"<<endl;
    for(int i=0;i<4;i++)
    {
        freeships[i]=1+i;//нулевой - четырехпалубник: одна штука
    }
    shipsalive=10;
    shiptype=4;
    gui->myfield->clear();
}
