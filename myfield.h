#ifndef MYFIELD_H
#define MYFIELD_H

//#include <QObject>
#include <iostream>
#include <battlefield.h>
#include <fstream>
class myfield : public battlefield
{
private:
    void blink(int x,int y);
public:
    myfield();
    ~myfield();
    int put(int x, int y);
    int strike(int x,int y);
    void ai_placement();
    void save();
    void load();
    friend ostream & operator<<(ostream&stream,myfield & o);
    friend istream & operator>>(istream&stream,myfield & o);
    void resetfield();
};

#endif // MYFIELD_H
