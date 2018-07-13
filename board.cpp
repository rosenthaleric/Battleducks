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

Board::Board(bool is_player, bool* b)
    : is_player_board_(is_player), running_(b)
{
    // initiate tiles
    for(int i = 0; i < 100; i++) {
        Tile* tile = new Tile(0, i);
        tiles_.push_back(tile);
    }

    if(!is_player_board_) setupCPUBoard();
}

// check wether duckfamily of certain lenght can be horizontally placed on board
bool Board::isPlaceable(int index, int length){
    // check if index is in board
    if(index > 99 || index < 0) return false;
    //  check if start index and end index would be on same row
    if(index / 10 != (index + length - 1) / 10) return false;
    for(int i = index; i < index + length; i++) {
        if(tiles_[i]->getStatus() != 0) return false;
        // check space between families (horizontally only when they're in the same row)
        if(i-1 >= 0)  if(tiles_[i-1]->getStatus() != 0 && (i-1) / 10 == i / 10) return false;       // left
        if(i+1 < 100)  if(tiles_[i+1]->getStatus() != 0 && (i+1) / 10 == i / 10) return false;      // right
        if(i-10 >= 0)  if(tiles_[i-10]->getStatus() != 0) return false;                             // above
        if(i+10 < 100)  if(tiles_[i+10]->getStatus() != 0) return false;                            // below
    }
    return true;
}

void Board::resetTiles(){
    for(int i = 0; i < tiles_.size(); i++) {
        tiles_[i]->setStatus(0);
    }
}

void Board::resetDuckfamilies(){
    duckFamilies_.clear();
}

void Board::setDuckFamily(int index, int length) {
    DuckFamily* duckFam = new DuckFamily(index, length);
    for(int i = index; i < index + length; i++) {
        Tile* tile = tiles_[i];
        // set status to duck
        tile->setStatus(1);
        tile->setDuckFamily(duckFam);
    }
    duckFamilies_.insert(duckFam);
}

void Board::removeDuckFamily(int start, int length) {
    DuckFamily* toBeRemoved = tiles_[start]->getDuckFamily();
    for(int i = start; i < start + length; i++) {
        tiles_[i]->setStatus(0);
    }
    duckFamilies_.erase(toBeRemoved);
}

std::set<DuckFamily*> Board::getDuckFamilies() {
    return duckFamilies_;
}

int Board::getFamilyStart(int i) {
    return tiles_[i]->getDuckFamily()->getStart();
}

int Board::getFamilyLength(int i) {
    return tiles_[i]->getDuckFamily()->getLength();
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

bool Board::shoot(int index) {
    int status = tiles_[index]->getStatus();
    if(status == 0) {
        tiles_[index]->setStatus(2);
        return false;
    }
    DuckFamily* duckFamily = tiles_[index]->shootDuck();
    if(duckFamily->isDestroyed()) {
        duckFamilies_.erase(duckFamily);
    }
    return true;
}

bool Board::isPlayerBoard() {
    return is_player_board_;
}

void Board::placeRandomly(int length) {
    std::random_device rd;
    std::mt19937 e2(rd());
    std::uniform_real_distribution<float> dist(0, 100);
    int index;

    while(true) {
        index = std::floor(dist(e2));
        if(isPlaceable(index, length)) {
            setDuckFamily(index, length);
            break;
        }
    }
}

// randomly places duckfamilies on cpu board
void Board::setupCPUBoard() {
    for(int i = 0; i<10; i++) {
        if(i == 0) placeRandomly(5);
        else if(i < 3) placeRandomly(4);
        else if(i < 6) placeRandomly(3);
        else placeRandomly(2);
    }
}

bool Board::running() {
    return *running_;
}

void Board::setRunning(bool b) {
    *running_ = b;
}

