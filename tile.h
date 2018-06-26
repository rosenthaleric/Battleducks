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
    void setShip(Ship*);

private:
    /**
     *  0 = neutral
     *  1 = duck
     *  2 = destroyed neutral
     *  3 = destroyed duck
     */
    int index_;
    int status_ = 0;
    Ship* ship_;
};

Tile::Tile(int i, int s) : status_(s) {}

int Tile::getStatus() {
    return status_;
}

void Tile::setStatus(int newStatus) {
    status_ = newStatus;
}

void Tile::setDuck(Ship* newShip) {
    ship_ = newShip;
}

#endif // TILE_H
