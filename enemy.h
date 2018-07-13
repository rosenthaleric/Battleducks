#ifndef ENEMY_H
#define ENEMY_H
#include "board.h"

class BoardView;
class Enemy
{
public:
    Enemy(BoardView* bw, Board* b);
    void shoot();

private:
    int last_shot_;
    Board* player_board_;
    BoardView* bw_;
};
#endif // ENEMY_H
