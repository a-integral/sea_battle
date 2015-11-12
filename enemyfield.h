#ifndef ENEMYFIELD_H
#define ENEMYFIELD_H

#include <battlefield.h>
#include "gameover_window.h"
#include <fstream>
class enemyfield : public battlefield
{
private:
    void ai_strike();
    int lasthitstate[4];//x,y,сатус определения направления,направление атаки, 1-не определено
public:
    battlefield* playerfield;
    gameover_window * gwptr;
    enemyfield(battlefield*pf=0);
    void ai_placement();
    int put(int x, int y);
    int strike(int x,int y);
    void save();
    void load();
    friend ostream & operator<<(ostream&stream,enemyfield & o);
    friend istream & operator>>(istream&stream,enemyfield & o);
    void resetfield();
signals:

public slots:
};

#endif // ENEMYFIELD_H
