#ifndef TILE_H
#define TILE_H

#include "duckfamily.h"

class Tile
{
public:
    Tile(int status = 0);

    void setStatus(int);
    int getStatus();
    void setDuck(DuckFamily*);
    DuckFamily* getDuck();
    DuckFamily* shootDuck();

private:
    int index_;
    int status_ = 0;
    DuckFamily* duck_;
};

#endif // TILE_H
