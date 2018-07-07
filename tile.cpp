#include "tile.h"
#include "duckfamily.h"

/**
 *  Represents a tile on the gameboard with a designated index.
 *  A tile either has a duck or is neutral, represented by its status.
 */

Tile::Tile(int s, int i) : status_(s), index_(i) {}

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


void Tile::setDuckFamily(DuckFamily* duckFam) {
    duckFam_ = duckFam;
}

DuckFamily* Tile::getDuckFamily() {
    return duckFam_;
}

DuckFamily* Tile::shootDuck() {
    duckFam_->popDuck(index_);
    setStatus(3);
    return duckFam_;
}
