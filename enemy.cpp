#include <random>
#include "enemy.h"
#include "board.h"
#include "boardview.h"
#include <iostream>
#include <QTimer>

Enemy::Enemy(QObject* parent, BoardView* bw, Board* b)
    : QObject(parent),
      bw_(bw),player_board_(b),
      last_shot_(-1) {}

void Enemy::shoot() {
    if(player_board_->mode() != 2) {
        return;
    }
    std::random_device rd;
    std::mt19937 e2(rd());
    std::uniform_real_distribution<float> dist(0, 100);
    // chance to make a random move or no last shot
    bool shot;
    int index;
    if(last_shot_ == -1) {
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
        else if(last_shot_ / 10 == (last_shot_ + 2) / 10 && player_board_->shootable(last_shot_ + 2)) index = last_shot_ + 2;
        else if(last_shot_ / 10 == (last_shot_ - 3) / 10 && player_board_->shootable(last_shot_ - 3)) index = last_shot_ - 3;
        else if(last_shot_ / 10 == (last_shot_ + 3) / 10 && player_board_->shootable(last_shot_ + 3)) index = last_shot_ + 3;
        else if(last_shot_ / 10 == (last_shot_ - 4) / 10 && player_board_->shootable(last_shot_ - 4)) index = last_shot_ - 4;
        else if(last_shot_ / 10 == (last_shot_ + 4) / 10 && player_board_->shootable(last_shot_ + 4)) index = last_shot_ + 4;
        else if(last_shot_ / 10 == (last_shot_ - 5) / 10 && player_board_->shootable(last_shot_ - 5)) index = last_shot_ - 5;
        else if(last_shot_ / 10 == (last_shot_ + 5) / 10 && player_board_->shootable(last_shot_ + 5)) index = last_shot_ + 5;
        else {
            last_shot_ = -1;
            index = std::floor(dist(e2));
            while(!player_board_->shootable(index)) {
                index = std::floor(dist(e2));
            }
        }
        shot = player_board_->shoot(index);
    }
    bw_->enemyAction(shot);
    if(shot && !player_board_->getDuckFamilies().empty()) {
        QTimer::singleShot(500, this, SLOT(shoot()));
    } else if(!player_board_->getDuckFamilies().empty()) {
        player_board_->setMode(1);
        last_shot_ = -1;
    }
}
