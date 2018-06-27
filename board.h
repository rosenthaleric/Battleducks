#ifndef BOARD_H
#define BOARD_H

#include "tile.h"
#include "duckfamily.h"

#include <vector>
#include <set>

class Board
{
public:
    Board();
    bool check(int, int);
    void setDuck(int, int);
    void shoot(int);
    bool shootable(int);
    int getTileStatus(int, int);
private:
    std::vector<Tile*> tiles_;
    std::set<DuckFamily*> duckFamilies_;
};
#endif // BOARD_H
