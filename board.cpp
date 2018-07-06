#include "board.h"
#include "tile.h"
#include "duckfamily.h"
#include <iostream>
#include <random>

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

Board::Board(bool is_player)
    : is_player_board_(is_player)
{
    // initiate tiles
    for(int i = 0; i < 100; i++) {
        Tile* tile = new Tile(0);
        tiles_.push_back(tile);
    }

    if(!is_player_board_) setupCPUBoard();
}

// check wether duckfamily of certain lenght can be horizontally placed on board
bool Board::isPlaceable(int index, int length){
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

int Board::getTileStatus(int i) {
    return tiles_[i]->getStatus();
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

bool Board::isPlayerBoard() {
    return is_player_board_;
}

// randomly places duckfamilies on cpu board
void Board::setupCPUBoard() {
    std::random_device rd;
    std::mt19937 e2(rd());
    std::uniform_real_distribution<float> dist(0, 100);
    bool placeable = false;
    int index;

    // 4x2
    for(int i=0; i<4; ++i) {
        while(!placeable) {
            index = std::floor(dist(e2));
            if(isPlaceable(index, 2)) placeable = true;
        }
        setDuck(index, 2);
        placeable = false;
    }
    // 3x3
    for(int i=0; i<3; ++i) {
        while(!placeable) {
            index = std::floor(dist(e2));
            if(isPlaceable(index, 3)) placeable = true;
        }
        setDuck(index, 3);
        placeable = false;
    }
    // 2x4
    for(int i=0; i<2; ++i) {
        while(!placeable) {
            index = std::floor(dist(e2));
            if(isPlaceable(index, 4)) placeable = true;
        }
        setDuck(index, 4);
        placeable = false;
    }
    // 1x5
    while(!placeable) {
        index = std::floor(dist(e2));
        if(isPlaceable(index, 5)) placeable = true;
    }
    setDuck(index, 5);
}
