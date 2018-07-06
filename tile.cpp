#include "tile.h"
#include "duckfamily.h"

/**
 *  Represents a tile on the gameboard with a designated index.
 *  A tile either has a duck or is neutral, represented by its status.
 */

Tile::Tile(int s) : status_(s) {}

int Tile::getStatus() {
    return status_;
}


/**
 *  0 = neutral
 *  1 = duck
 *  2 = destroyed neutral
 *  3 = destroyed duck
 */
void Tile::setStatus(int newStatus) {
    status_ = newStatus;
}

void Tile::setDuck(DuckFamily* newDuck) {
    duck_ = newDuck;
}

DuckFamily* Tile::getDuck() {
    return duck_;
}

DuckFamily* Tile::shootDuck() {
    duck_->popDuck(index_);
    setStatus(3);
    return duck_;
}
