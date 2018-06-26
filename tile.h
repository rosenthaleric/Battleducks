#include "duck.h"

#ifndef TILE_H
#define TILE_H

/**
 *  Represents a tile on the gameboard with a designated index.
 *  A tile either has a duck or is neutral, represented by its status.
 */

class Tile
{
public:

    Tile(int status = 0);

    void setStatus(int);
    int getStatus();
    void setDuck(Duck*);
    Duck* getDuck();

private:
    /**
     *  0 = neutral
     *  1 = duck
     *  2 = destroyed neutral
     *  3 = destroyed duck
     */
    int index_;
    int status_ = 0;
    Duck* duck_;
};

Tile::Tile(int i, int s) : status_(s) {}

int Tile::getStatus() {
    return status_;
}

void Tile::setStatus(int newStatus) {
    status_ = newStatus;
}

void Tile::setDuck(Duck* newDuck) {
    duck_ = newDuck;
}

Duck* Tile::getDuck() {
    return duck_;
}

#endif // TILE_H
