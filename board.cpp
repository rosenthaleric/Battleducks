#include "board.h"
#include "tile.h"
#include "duck.h"

#include <vector>
#include <set>

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
        Duck* duck = new Duck(index, length);
        ducks_.insert(duck);
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
    Duck* duck = tiles_[index]->shootDuck();
    if(duck->isDestroyed()) {
        ducks_.erase(duck);
    }
}
