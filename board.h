#include <vector>
#include <set>
#include "tile.h"

class Board
{
public:
    Board();
    bool check(int, int);
    void setDuck(int, int);
    void shoot(int);
    bool shootable(int);
private:
    std::vector<Tile> tiles_;
    std::set<Duck> ducks_;
};

Board::Board(){
    ducks_ = new std::set<Duck>();
    tiles_ = new std::vector<Tile>(100);
    for(int i = 0; i < 100; i++) {
        tiles_[i] = new Tile();
    }
}

bool Board::check(int index, int length){
    // check if index is in board
    if(index > 99 || index < 0) return false;
    //  check if start index and end index would be on same row
    if(index / 10 != (index + length) / 10) return false;
    for(int i = index; i < index + length; i++) {
        if(tiles_[i].getStatus() != 0) return false;
    }
    return true;
}

void Board::setDuck(int index, int length) {
    for(int i = index; i < index + length; i++) {
        Tile* tile = tiles_[i];
        // set status to duck
        *tile->setStatus(1);
        Duck* duck = new Duck(index, length);
        ducks_.insert(*duck);
        *tile->setDuck(*duck);
    }
}

bool Board::shootable(int index) {
    // check if index is in board
    if(index > 99 || index < 0) return false;
    int status = tiles_[index].getStatus();
    return (status == 0 || status == 1);
}

void Board::shoot(int index) {
    int status = tiles_[index].getStatus();
    if(status == 0) {
        tiles_[index].setStatus(2);
        return;
    }
    Duck* duck = tiles_[index].shootDuck();
    if(*duck->isDestroyed()) {
        ducks_.erase(*duck);
    }
}
