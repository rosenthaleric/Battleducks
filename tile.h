#include "duck.h"

#ifndef TILE_H
#define TILE_H

class Tile
{
public:
    Tile(int status = 0);

    void setStatus(int);
    int getStatus();
    void setDuck(Duck*);
    Duck* getDuck();
    Duck* shootDuck();

private:
    int index_;
    int status_ = 0;
    Duck* duck_;
};

#endif // TILE_H
