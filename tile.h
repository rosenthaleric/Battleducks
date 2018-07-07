#ifndef TILE_H
#define TILE_H

#include "duckfamily.h"

class Tile
{
public:
    Tile(int status = 0, int index = 0);

    void setStatus(int);
    int getStatus();
    void setDuckFamily(DuckFamily*);
    DuckFamily* getDuckFamily();
    DuckFamily* shootDuck();

private:
    int index_;
    int status_ = 0;
    DuckFamily* duckFam_;
};

#endif // TILE_H
