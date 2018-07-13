#include <random>
#include "enemy.h"
#include "board.h"
#include "boardview.h"
#include <iostream>
#include <thread>
#include <chrono>
Enemy::Enemy(BoardView* bw, Board* b) : bw_(bw),player_board_(b), last_shot_(-1) {
}

void Enemy::shoot() {
    std::random_device rd;
    std::mt19937 e2(rd());
    std::uniform_real_distribution<float> dist(0, 100);
    // chance to make a random move or no last shot
    int chance = std::floor(dist(e2));
    bool shot;
    int index;
    if(last_shot_ == -1 || chance < 40) {
        index = std::floor(dist(e2));
        while(!player_board_->shootable(index)) {
            index = std::floor(dist(e2));
        }
        shot = player_board_->shoot(index);
        if(shot) last_shot_ = index;
    } else {
        if(last_shot_ / 10 == (last_shot_ - 1) / 10 && player_board_->shootable(last_shot_ - 1)) index = last_shot_ - 1;
        else if(last_shot_ / 10 == (last_shot_ + 1) / 10 && player_board_->shootable(last_shot_ + 1)) index = last_shot_ + 1;
        else if(last_shot_ / 10 == (last_shot_ - 2) / 10 && player_board_->shootable(last_shot_ - 2)) index = last_shot_ - 2;
        else if(last_shot_ / 10 == (last_shot_ + 3) / 10 && player_board_->shootable(last_shot_ + 3)) index = last_shot_ + 3;
        else if(last_shot_ / 10 == (last_shot_ - 3) / 10 && player_board_->shootable(last_shot_ - 3)) index = last_shot_ - 3;
        else if(last_shot_ / 10 == (last_shot_ - 4) / 10 && player_board_->shootable(last_shot_ - 4)) index = last_shot_ - 4;
        else if(last_shot_ / 10 == (last_shot_ + 4) / 10 && player_board_->shootable(last_shot_ + 4)) index = last_shot_ + 4;
        else if(last_shot_ / 10 == (last_shot_ - 5) / 10 && player_board_->shootable(last_shot_ - 5)) index = last_shot_ - 5;
        else if(last_shot_ / 10 == (last_shot_ + 5) / 10 && player_board_->shootable(last_shot_ + 5)) index = last_shot_ + 5;
        else {
            last_shot_ = -1;
            shoot();
            return;
        }
        shot = player_board_->shoot(index);
    }
    bw_->enemyAction(shot);
    std::this_thread::sleep_for(std::chrono::seconds(4));
    if(shot) {
        shoot();
    } else {
        last_shot_ = -1;
    }
}
