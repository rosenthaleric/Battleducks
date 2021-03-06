#ifndef BOARD_H
#define BOARD_H

#include "tile.h"
#include "duckfamily.h"
#include <memory>
#include <vector>
#include <set>

class Board
{
public:
    Board(bool is_player_board, int* m);
    bool isPlaceable(int, int);
    void setDuckFamily(int, int);
    void removeDuckFamily(int, int);
    std::set<DuckFamily*> getDuckFamilies();
    int getFamilyStart(int);
    int getFamilyLength(int);
    bool shoot(int);
    bool shootable(int);
    int getTileStatus(int);
    bool isPlayerBoard();
    bool placeRandomly(int);
    void setupCPUBoard();
    void resetDuckfamilies();
    void resetTiles();
    int mode();
    void setMode(int);

private:
    std::vector<Tile*> tiles_;
    std::set<DuckFamily*> duckFamilies_;
    bool is_player_board_;
    // game status in mode
    // 0 -> setup
    // 1 -> running
    // 2 -> pause
    int* mode_;
};
#endif // BOARD_H
