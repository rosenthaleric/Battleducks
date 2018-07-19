#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsSceneMouseEvent>
#include <iostream>
#include <set>
#include <QTimer>
#include "duckfamily.h"
#include "board.h"
#include "boardView.h"
#include "enemy.h"

/**
 * Responsible for drawing and updating the tiles of a board to a given scene
 * and handling mouse events and setup signals.
 */

BoardView::BoardView(QObject *parent, Board* board)
    : QGraphicsScene(parent),
      board_(board),
      previewMode_(false),
      placeablePreview_(false),
      movableLength_(0),
      previewStartIndex_(0),
      oldDuckIndex_(0),
      oldDuckLength_(0)
{
    tiles_ = std::vector<QGraphicsPixmapItem*>(100);
    tiles_textures_ = std::vector<QPixmap>(8);
    tiles_textures_[0] = QPixmap(":/resources/assets/water_tile.jpg").scaled(QSize(25, 25));
    tiles_textures_[2] = QPixmap(":/resources/assets/water_tile_destroyed.jpg").scaled(QSize(25, 25));
    tiles_textures_[1] = QPixmap(":/resources/assets/duck_tile.png").scaled(QSize(25, 25));
    tiles_textures_[3] = QPixmap(":/resources/assets/duck_tile_destroyed.png").scaled(QSize(25, 25));

    // preview placement tiles
    tiles_textures_[4] = QPixmap(":/resources/assets/placeable_watertile.jpg").scaled(QSize(25, 25));
    tiles_textures_[5] = QPixmap(":/resources/assets/nonplaceable_watertile.jpg").scaled(QSize(25, 25));
    tiles_textures_[6] = QPixmap(":/resources/assets/nonplaceable_duck_tile.png").scaled(QSize(25, 25));
    tiles_textures_[7] = QPixmap(":/resources/assets/duck_tile_bw.png").scaled(QSize(25, 25));
}

// DRAWING per row, left to right
void BoardView::drawBoard() {
    this->clear();

    //for checking family count on board
    if (board_->isPlayerBoard()) {
        std::cout << board_->getDuckFamilies().size() << std::endl;
    }

    for(int y = 0; y < 10; y++) {
        for(int x = 0; x < 10; x++) {
         int i;

         /**
           * If the preview mode is enabled the specified preview texture is loaded. Start and end of the
           * preview tile sequence is dependant on the aforeset previewStartIndex and movableLength. Red or Green
           * is determined by the placeablePreview flag. The clicked duckfamily is always gray.
           */
         if(previewMode_ && x+y*10 >= oldDuckIndex_ && x+y*10 < oldDuckIndex_ + oldDuckLength_) i = 7;  // gray duck
         else if(previewMode_ && x+y*10 >= previewStartIndex_
                 && x+y*10 < previewStartIndex_ + movableLength_ && placeablePreview_) i = 4;  //green water
         else if(previewMode_ && x+y*10 >= previewStartIndex_
                 && x+y*10 < previewStartIndex_ + movableLength_ && !placeablePreview_) {
             if(board_->getTileStatus(x + y * 10) == 0) i = 5;  // red water
             if(board_->getTileStatus(x + y * 10) == 1) i = 6;  // red duck
         }
         else i = board_->getTileStatus(x + y * 10);

         if (!board_->isPlayerBoard() && i == 1) i = 0;
         QGraphicsPixmapItem *tile = this->addPixmap(tiles_textures_[i]);
         tile->moveBy(27*x, 27*y);
         tiles_.at(x + y * 10) = tile;
        }
    }
    update();
}

// shooting on enemy board
void BoardView::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) {
    if(!board_->isPlayerBoard() && board_->mode() == 1) {
        for (int i = 0; i < tiles_.size(); i++) {
            if (tiles_[i]->sceneBoundingRect().contains(event->scenePos())) {
                if(board_->shootable(i)) {
                    bool shot = board_->shoot(i);
                    std::cout << "drawing" << std::endl;
                    drawBoard();
                    // play duck sound and check if lost // if no duck was shot, enemy shoots
                    if(shot) {
                        emit duckSound();
                        if(board_->getDuckFamilies().empty()) emit cpu_lost();
                    } else {
                        board_->setMode(2);
                        std::cout << "setMode to 2 : " << board_->mode() << std::endl;
                        QTimer::singleShot(1000, enemy_, SLOT(shoot()));
                    }
                }
            }
        }
    // starting the previewMode to move ducks on players board
    } else if(board_->mode() == 0 && board_->isPlayerBoard()) {
            for (int i = 0; i < tiles_.size(); i++) {
                if (tiles_[i]->sceneBoundingRect().contains(event->scenePos())) {
                    if(board_->getTileStatus(i) == 1) {
                        movableLength_ = board_->getFamilyLength(i);
                        oldDuckIndex_ = board_->getFamilyStart(i);
                        oldDuckLength_ = movableLength_;
                        previewMode_ = true;
                    }
                }
            }
      }
}

// only fired when previewMode is enabled by doubleclicking on a set duck
void BoardView::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    if(previewMode_) {
        int length = movableLength_;
        for (int i = 0; i < tiles_.size(); i++) {
            if (tiles_[i]->sceneBoundingRect().contains(event->scenePos())) {

                // DRAW GREEN PREVIEW TILES
                if(board_->isPlaceable(i, length)) {
                    placeablePreview_ = true;
                    previewStartIndex_ = i;
                    drawBoard();
                }

                // DRAW RED PREVIEW TILES
                else {
                    placeablePreview_ = false;
                    previewStartIndex_ = i;
                    // prevent drawing red tiles across two rows
                    while(previewStartIndex_ / 10 != (previewStartIndex_ + movableLength_ - 1) / 10) {
                        movableLength_--;
                    }
                    drawBoard();
                    movableLength_ = length;    // reset movableLength_ as it gets decremented above
                }
            }
        }
    }
}

// in previewMode: place a new duck if possible or leave previewMode and everything stays the same
void BoardView::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if(previewMode_ && event->button() == Qt::LeftButton) {
        if(!board_->isPlaceable(previewStartIndex_, oldDuckLength_)) {
            previewMode_ = false;
        }
        else {
            previewMode_ = false;
            board_->removeDuckFamily(oldDuckIndex_, oldDuckLength_);
            board_->setDuckFamily(previewStartIndex_, oldDuckLength_);
        }
        movableLength_ = 0;
        previewStartIndex_ = 0;
        oldDuckIndex_ = 0;
        oldDuckLength_ = 0;
        drawBoard();
    }
    else if(board_->isPlayerBoard() && event->button() == Qt::RightButton && board_->mode() == 0) {
        for (int i = 0; i < tiles_.size(); i++) {
            if (tiles_[i]->sceneBoundingRect().contains(event->scenePos())) {
                if(board_->getTileStatus(i) == 1) {
                    emit returnFamily(board_->getFamilyLength(i));
                    board_->removeDuckFamily(board_->getFamilyStart(i), board_->getFamilyLength(i));
                    drawBoard();
                }
            }
        }
    }
}

// called by enemy, updates board-drawing and checks if enemy shot a duck for sound and loss
void BoardView::enemyAction(bool shot) {
    if(shot) {
        emit duckSound();
        if(board_->getDuckFamilies().empty()) emit player_lost();
    }
    drawBoard();
}

void BoardView::setEnemy(Enemy* enemy) {
    enemy_ = enemy;
}

// receiver slot for signal from the player setup to place a family
void BoardView::receiveFamily(int length) {
    board_->placeRandomly(length);
    emit duckSound();
    drawBoard();
}

void BoardView::win() {
    std::cout << "Won!" << std::endl;
    board_->setMode(2);
    colorTiles(4);
    update();
}

void BoardView::lose() {
    std::cout << "LOST! :-(" << std::endl;
    board_->setMode(2);
    colorTiles(5);
    update();
}

void BoardView::colorTiles(int i) {
    for(int x = 0; x < 10; x++) {
        for(int y = 0; y < 10; y++) {
            QGraphicsPixmapItem *tile = this->addPixmap(tiles_textures_[i]);
            tile->moveBy(27 * x, 27 * y);
            tiles_.at(x + y * 10) = tile;
        }
    }
}

void BoardView::start() {
    if(board_->mode() == 0 && board_->isPlayerBoard() && board_->getDuckFamilies().size() == 10) {
        std::cout << "Start!" << std::endl;
        board_->setRunning(true);
        board_->setMode(1);
    }
}
