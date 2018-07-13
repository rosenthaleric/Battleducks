#include <random>
#include "enemy.h"

Enemy::Enemy(Board* b) : player_board_(b), last_shot_(-1) {
    rd = new std::random_device();
    e2 = new std::mt19937(rd);
    dist = new std::uniform_real_distribution<float>(0, 100);
}
