#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsSceneMouseEvent>
#include <iostream>

#include "board.h"
#include "boardView.h"

/**
 * Responsible for drawing the tiles of a board to a given scene.
 * TODO callbacks and Signals
 */

BoardView::BoardView(QObject *parent, Board* board)
    : QGraphicsScene(parent),
      board_(board)
{
    //board_ = Board();
    tiles_ = std::vector<QGraphicsPixmapItem*>(100);
    tiles_textures_ = std::vector<QPixmap>(4);
    tiles_textures_[0] = QPixmap(":/resources/assets/water_tile.jpg").scaled(QSize(25, 25));
    tiles_textures_[2] = QPixmap(":/resources/assets/water_tile_destroyed.jpg").scaled(QSize(25, 25));
    tiles_textures_[1] = QPixmap(":/resources/assets/duck_tile.png").scaled(QSize(25, 25));
    tiles_textures_[3] = QPixmap(":/resources/assets/duck_tile_destroyed.png").scaled(QSize(25, 25));
}

// draw a board // per row, left to right
void BoardView::drawBoard() {
    this->clear();
    for(int y = 0; y < 10; y++) {
        for(int x = 0; x < 10; x++) {
         int i = board_->getTileStatus(x + y * 10);

         if (!board_->isPlayerBoard() && i == 1) i = 0;
         QGraphicsPixmapItem *tile = this->addPixmap(tiles_textures_[i]);
         tile->moveBy(27*x, 27*y);
         tile->setFlags(QGraphicsItem::ItemIsSelectable);
         tiles_.at(x + y * 10) = tile;
        }
    }
}

void BoardView::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) {
    if(!board_->isPlayerBoard()) {
        for (int i = 0; i < tiles_.size(); i++) {
            if (tiles_[i]->sceneBoundingRect().contains(event->scenePos())) {
                if(board_->shootable(i)) board_->shoot(i);
                tiles_[i]->setSelected(false);
            }
        }
        drawBoard();
    }
}
