#include "enemyfield.h"
#include "mainwindow.h"
enemyfield::enemyfield(battlefield * pf)
{
    playerfield=pf;
    for (int i=0;i<4;i++) lasthitstate[i]=-1;
}

int enemyfield::strike(int x,int y)
{
    if (!playerfield->ready()) return -1;
    if (!this->ready()) return -1;
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
        //cout<<"result"<<hit<<endl;
    }
    if (hit==-1) return -1;//уже били эту палубу
    if (hit==0)
    {
        QTableWidgetItem * ti=gui->enemyfield->item(y,x);
        if(!ti){
            ti=new QTableWidgetItem();
        }
        gui->enemyfield->setItem(y,x,ti);
        ti->setText("-");
        //cout<<"hit0"<<endl;
        //cout<<x<<y<<endl;
    }
    if (hit==1)
    {
        //cout<<"hit1"<<endl;
        // cout<<x<<y<<endl;
       gui->enemyfield->item(y,x)->setText("X");
       gui->enemyfield->item(y,x)->setBackgroundColor(QColor(255,100,100));
    }
    if (hit==2)
    {
       //cout<<"hit2"<<endl;
       // cout<<x<<y<<endl;
       shipsalive--;
       if (shipsalive==0)
       {
           gwptr->settext("Вы выиграли");
           gwptr->show();
       }
       int nship=ships[id-1].getn();
       int xship=ships[id-1].getx();
       int yship=ships[id-1].gety();
       int horship=ships[id-1].gethor();
       gui->enemyfield->item(y,x)->setText("X");
        cout<<nship<<xship<<yship<<horship<<endl;
       if(horship)
       {
           for (int i=xship-1;i<=xship+nship;i++)
           {
               if (validpos(i,yship-1))
               {
                   field[i][yship-1]=-1;
                   QTableWidgetItem * ti=gui->enemyfield->item(yship-1,i);
                   if(!ti){
                       ti=new QTableWidgetItem();
                        gui->enemyfield->setItem(yship-1,i,ti);
                   }
                   gui->enemyfield->item(yship-1,i)->setText("-");

               }//проставим "-" сверху
               if (validpos(i,y+1))
               {
                    field[i][yship+1]=-1;
                   QTableWidgetItem * ti=gui->enemyfield->item(yship+1,i);
                   if(!ti){
                       ti=new QTableWidgetItem();
                       gui->enemyfield->setItem(yship+1,i,ti);
                   }

                   gui->enemyfield->item(yship+1,i)->setText("-");//проставим "-" снизу
               }
           }
           if (validpos(xship-1,yship))
           {
                field[xship-1][y]=-1;
               QTableWidgetItem * ti=gui->enemyfield->item(yship,xship-1);
               if(!ti){
                   ti=new QTableWidgetItem();
                   gui->enemyfield->setItem(yship,xship-1,ti);
               }
                gui->enemyfield->item(yship,xship-1)->setText("-");

           }//слева
           if (validpos(xship+nship,yship))
           {
               field[xship+nship][y]=-1;
               QTableWidgetItem * ti=gui->enemyfield->item(yship,xship+nship);
               if(!ti){
                   ti=new QTableWidgetItem();
                   gui->enemyfield->setItem(yship,xship+nship,ti);
               }
               gui->enemyfield->item(yship,xship+nship)->setText("-");
           }//справа
       }
       else
       {
           for (int i=yship-1;i<=yship+nship;i++)
           {
               if (validpos(xship-1,i))
               {
                   field[xship-1][i]=-1;
                   QTableWidgetItem * ti=gui->enemyfield->item(i,xship-1);
                   if(!ti){
                       ti=new QTableWidgetItem();
                       gui->enemyfield->setItem(i,xship-1,ti);
                   }
                   gui->enemyfield->item(i,xship-1)->setText("-");
                  ;
               }//проставим "-" слева
               if (validpos(xship+1,i))
               {
                   field[xship+1][i]=-1;
                   QTableWidgetItem * ti=gui->enemyfield->item(i,xship+1);
                   if(!ti){
                       ti=new QTableWidgetItem();
                       gui->enemyfield->setItem(i,xship+1,ti);
                   }
                   gui->enemyfield->item(i,xship+1)->setText("-");
                 //проставим "-" справа
               }
           }
           if (validpos(xship,yship-1))
           {
               field[xship][yship-1]=-1;
               QTableWidgetItem * ti=gui->enemyfield->item(yship-1,xship);
               if(!ti){
                   ti=new QTableWidgetItem();
                   gui->enemyfield->setItem(yship-1,xship,ti);
               }
               gui->enemyfield->item(yship-1,xship)->setText("-");
           }//сверху
           if (validpos(xship,yship+nship))
           {
               field[xship][yship+nship]=-1;
               QTableWidgetItem * ti=gui->enemyfield->item(yship+nship,xship);
               if(!ti){
                   ti=new QTableWidgetItem();
                   gui->enemyfield->setItem(yship+nship,xship,ti);
               }
               gui->enemyfield->item(yship+nship,xship)->setText("-");
           }//снизу
       }
       gui->enemyfield->item(y,x)->setBackgroundColor(QColor(255,0,0));
    }
    if (!hit)
    {
        ai_strike();
    }
    return hit;
}

void enemyfield::ai_strike()
{

    int status=1;
    int x,y;
    //if (lasthitstate[0]==-1) status=1;
   while (status)
   {
       //cout<<status;
       if (lasthitstate[2]==-1)
       {//будем бить случайно, если в прошлый раз не ранили
        x=rand()%10;
        y=rand()%10;
        status=playerfield->strike(x,y);
        cout<<"хожу случайно"<<endl;
       }
       if(status==0) break;

/**/    if (status==2)
        {
            lasthitstate[2]=-1;
            lasthitstate[3]=-1;//убили, дальше бьем случайно
            cout<<"убил!"<<endl;
            if (playerfield->shipsalive==0)
            {
                gwptr->settext("Вы проиграли");
                gwptr->show();
            }
            continue;
        }
        if (status==1&&lasthitstate[2]==-1) //ранили,определение еще не начато, начнем, запомним куда ранили
        {
            lasthitstate[0]=x;
            lasthitstate[1]=y;
            lasthitstate[2]=1;//в следующий раз бить слева
        }
    if (lasthitstate[3]==-1&&lasthitstate[2]>0) //направление атаки не задано, определение начато

    {
        x=lasthitstate[0];
        y=lasthitstate[1];
        switch (lasthitstate[2])
        {
        case 1:if (validpos(x-1,y))
            {
                status=playerfield->strike(x-1,y);
                if (status==1)
                {
                    lasthitstate[3]=1;//напр. атаки - влево
                }
                else lasthitstate[2]++;
                //if (status==-1) lasthitstate[3]=3;//там уже били идем вправо
                //if (status==0) lasthitstate[3]=3;//пойдем вправо
            }
            else lasthitstate[2]++; //в этом направлении конец поля
            cout<<"пробуем слева"<<endl;
            break;
        case 2:if (validpos(x,y-1))
            {
                status=playerfield->strike(x,y-1);
                if (status==1)
                {
                    lasthitstate[3]=2;//вверх
                }
                else lasthitstate[2]++;
                //if (status==-1) lasthitstate[3]=4;//пойдем вниз
                //if (status==-1) lasthitstate[2]++;
            }
            else lasthitstate[2]++;
            cout<<"пробуем сверху"<<endl;
            break;
        case 3:if (validpos(x+1,y))
            {
                status=playerfield->strike(x+1,y);
                if (status==1)
                {
                    lasthitstate[3]=3;//вправо
                }
                else lasthitstate[2]++;
                //if (status==-1) lasthitstate[2]++;
            }
            else lasthitstate[2]++;
            cout<<"пробуем справа"<<endl;
            break;
        case 4:if (validpos(x,y+1))
            {

                status=playerfield->strike(x,y+1);
                if (status==1)
                {
                    lasthitstate[3]=4;//вниз
                }
                else lasthitstate[2]++;
                //if (status==-1) lasthitstate[2]++;
            }
            else lasthitstate[2]++;
            cout<<"пробуем снизу"<<endl;
            break;
        case 5:lasthitstate[2]=-1;
               cout<<"!!!неправильно!!!"<<endl;
               break;//не должно случиться

        }
        //lasthitstate[2]++;
    }
    if(!status) return;//при поиске не попали
       if (lasthitstate[3]>0&&lasthitstate[2]>0) //атакуем влево
       {
           cout<<"ai_works"<<endl;
           switch (lasthitstate[3])
           {
           case 1:
               cout<<"атака влево"<<endl;
            x=lasthitstate[0];
            y=lasthitstate[1];
            if (validpos(x-1,y))
            {
             status=playerfield->strike(x-1,y);
            }
            else lasthitstate[3]=3;

            if (status==1)
            {
                lasthitstate[0]--;
            }
            if (status==0)
            {
                lasthitstate[3]=3;
            }
            if(status==-1&&playerfield->field[x-1][y]>0)
            {
                lasthitstate[0]--;
            }
            if(status==-1&&playerfield->field[x-1][y]==-1)
            {
                lasthitstate[3]=3;
            }
           break;
           case 2:
               cout<<"атака вверх"<<endl;
            x=lasthitstate[0];
            y=lasthitstate[1];
            if (validpos(x,y-1))
            {
             status=playerfield->strike(x,y-1);
            }
            else lasthitstate[3]=4;
            if (status==1)
            {
                lasthitstate[1]--;
            }
            if (status==0)
            {
                lasthitstate[3]=4;
            }
            if(status==-1&&playerfield->field[x][y-1]>0)
            {
                lasthitstate[1]--;
            }
            if(status==-1&&playerfield->field[x][y-1]==-1)
            {
                lasthitstate[3]=4;
            }
           break;
           case 3:
               cout<<"атака вправо"<<endl;
            x=lasthitstate[0];
            y=lasthitstate[1];
            if (validpos(x+1,y))
            {
             status=playerfield->strike(x+1,y);
            }
            else lasthitstate[3]=1;
            if (status==1)
            {
                lasthitstate[0]++;
            }
            if (status==0)
            {
                lasthitstate[3]=1;
            }
            if(status==-1&&playerfield->field[x+1][y]>0)
            {
                lasthitstate[0]++;
            }
            if(status==-1&&playerfield->field[x+1][y]==-1)
            {
                lasthitstate[3]=1;
            }
           break;
           case 4:
               cout<<"атака вниз"<<endl;
            x=lasthitstate[0];
            y=lasthitstate[1];
            if (validpos(x,y+1))
            {
             status=playerfield->strike(x,y+1);
            }
            else lasthitstate[3]=2;
            if (status==1)
            {
                lasthitstate[1]++;
            }
            if (status==0)
            {
                lasthitstate[3]=2;
            }
            if(status==-1&&playerfield->field[x][y+1]>0)
            {
                lasthitstate[1]++;
            }
            if(status==-1&&playerfield->field[x][y+1]==-1)
            {
                lasthitstate[3]=2;
            }
           break;
          }
       }
    /**/
   }

}

void enemyfield::ai_placement()
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
    }
    while(status);
}

int enemyfield::put(int x, int y)
{
        int n=shiptype;
        if (this->currentstate==0) return -1; //расстановка закончена
        if (freeships[4-shiptype]==0)
        {
            shiptype--;
            return -1;
        }
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
                   QTableWidgetItem * ti=gui->enemyfield->item(y+i,x);

                 if(!ti){
                   ti=new QTableWidgetItem();
                   gui->enemyfield->setItem(y+i,x,ti);
                   //cout<<"created"<<endl;
                 }

               //cout<<"setting"<<endl;
               //ti->setBackgroundColor(QColor(255,255,0));
               //ti->setText("X");   //отладка отображаем корабли компа
               }

           }
           if (hor_state)
           {
               cout<<"hor"<<endl;
               cout<<hor_state<<endl;
               for(int i=0;i<n;i++){
                   field[x+i][y]=id;
                   //cout<<"point"<<endl;
                   QTableWidgetItem * ti=gui->enemyfield->item(y,x+i);
                   cout<<ti<<endl;
                   if(!ti){
                       ti=new QTableWidgetItem();
                       gui->enemyfield->setItem(y,x+i,ti);
                       //cout<<"created"<<endl;
                   }
                   //cout<<"setting"<<endl;
                   //ti->setBackgroundColor(QColor(255,255,0));
                   //ti->setText("X");
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
               return 0;
           }
            return 1;
           cout<<"______________"<<endl;
}


ostream & operator<<(ostream&stream,enemyfield & o)
{
    cout<<"save enemyfield\n";
    stream<<o.currentstate<<endl;
    for (int i=0;i<4;i++) stream<<o.freeships[i]<<endl;
    stream<<o.shiptype<<endl<<o.shipsalive<<endl;
    for (int i=0;i<10;i++) stream<<o.ships[i];
    stream<<o.hor_state<<endl;
    for (int i=0;i<10;i++)
        for (int j=0;j<10;j++)
            stream<<o.field[j][i]<<endl;
    for (int i=0;i<4;i++) stream<<o.lasthitstate[i]<<endl;
    return stream;
}
istream & operator>>(istream&stream,enemyfield & o)
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
    for (int i=0;i<4;i++) stream>>o.lasthitstate[i];
    return stream;
}
void enemyfield::load()
{
    this->resetfield();
    ifstream in("enemyfield.dat",ios::in);
    in>>*this;
    //перерисовываем интерфейс
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++)
        {
            int x=j;
            int y=i;
            if (field[j][i]==-1)
            {
                QTableWidgetItem * ti=gui->enemyfield->item(y,x);
                if(!ti){
                    ti=new QTableWidgetItem();
                }
                gui->enemyfield->setItem(y,x,ti);
                ti->setText("-");
            }
            if (field[j][i]>0)
            {
                int deckstate=ships[field[j][i]-1].getdeck(j,i);
                if (deckstate==-1)
                {
                    QTableWidgetItem * ti=gui->enemyfield->item(y,x);
                    if(!ti)
                    {
                        ti=new QTableWidgetItem();
                        gui->enemyfield->setItem(y,x,ti);
                    }
                    gui->enemyfield->item(y,x)->setText("X");
                    gui->enemyfield->item(y,x)->setBackgroundColor(QColor(255,100,100));
                }
                if (deckstate==1)
                {
                    QTableWidgetItem * ti=gui->enemyfield->item(y,x);
                    if(!ti)
                    {
                        ti=new QTableWidgetItem();
                        gui->enemyfield->setItem(y,x,ti);
                    }
                    //gui->enemyfield->item(y,x)->setText("X");
                    //gui->enemyfield->item(y,x)->setBackgroundColor(QColor(255,255,0));
                }

            }
        }
}
void enemyfield::save()
{
    ofstream out("enemyfield.dat",ios::out);
    out<<*this;
}
void enemyfield::resetfield()
{
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
    for (int i=0;i<4;i++) lasthitstate[i]=-1;
    gui->enemyfield->clear();
}
