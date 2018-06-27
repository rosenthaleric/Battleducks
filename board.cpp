#include "board.h"
#include "tile.h"
#include "duckfamily.h"

#include <vector>
#include <set>

/**
 * Represents a board entity.
 * A board contains a tiles- and a ducks container.
 * This class is responsible for checking if a duckFamily of a certain length
 * can be placed on the board, setting duckfamilies and adding them to the boards
 * container, shooting tiles (propagating shoot() to Tiles Object if there is
 * a duck) and setting their status.
 *
 * DuckFamilies return a destroyed status. If true, the corresponding duckFamily is erased
 * from the boards duck container, relevant for the game progress.
 */

Board::Board(){
    for(int i = 0; i < 100; i++) {
        tiles_.push_back(new Tile());
    }
}

bool Board::check(int index, int length){
    // check if index is in board
    if(index > 99 || index < 0) return false;
    //  check if start index and end index would be on same row
    if(index / 10 != (index + length) / 10) return false;
    for(int i = index; i < index + length; i++) {
        if(tiles_[i]->getStatus() != 0) return false;
    }
    return true;
}

void Board::setDuck(int index, int length) {
    for(int i = index; i < index + length; i++) {
        Tile* tile = tiles_[i];
        // set status to duck
        tile->setStatus(1);
        DuckFamily* duck = new DuckFamily(index, length);
        duckFamilies_.insert(duck);
        tile->setDuck(duck);
    }
}

bool Board::shootable(int index) {
    // check if index is in board
    if(index > 99 || index < 0) return false;
    int status = tiles_[index]->getStatus();
    return (status == 0 || status == 1);
}

void Board::shoot(int index) {
    int status = tiles_[index]->getStatus();
    if(status == 0) {
        tiles_[index]->setStatus(2);
        return;
    }
    DuckFamily* duckFamily = tiles_[index]->shootDuck();
    if(duckFamily->isDestroyed()) {
        duckFamilies_.erase(duckFamily);
    }
}
