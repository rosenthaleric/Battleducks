#ifndef BOARD_H
#define BOARD_H

#include "tile.h"
#include "duckfamily.h"

#include <vector>
#include <set>

class Board
{
public:
    Board(bool is_player_board);
    bool isPlaceable(int, int);
    void setDuck(int, int);
    void shoot(int);
    bool shootable(int);
    int getTileStatus(int);
    bool isPlayerBoard();
    void setupCPUBoard();
private:
    std::vector<Tile*> tiles_;
    std::set<DuckFamily*> duckFamilies_;
    bool is_player_board_;
};
#endif // BOARD_H
