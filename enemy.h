#ifndef ENEMY_H
#define ENEMY_H
#include <random>
#include "board.h"

class Enemy
{
public:
    Enemy(Board*);
    void shoot();

private:
    int last_shot_;
    Board* player_board_;
    std::random_device* rd;
    std::mt19937* e2;
    std::uniform_real_distribution<float>* dist;
}
#endif // ENEMY_H
