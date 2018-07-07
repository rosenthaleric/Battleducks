#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsSceneMouseEvent>
#include <iostream>
#include <set>
#include "duckfamily.h"
#include "board.h"
#include "boardView.h"

/**
 * Responsible for drawing the tiles of a board to a given scene.
 */

BoardView::BoardView(QObject *parent, Board* board)
    : QGraphicsScene(parent),
      board_(board),
      previewMode_(false),
      movableLength_(0),
      previewStartIndex_(0)
{
    tiles_ = std::vector<QGraphicsPixmapItem*>(100);
    tiles_textures_ = std::vector<QPixmap>(7);
    tiles_textures_[0] = QPixmap(":/resources/assets/water_tile.jpg").scaled(QSize(25, 25));
    tiles_textures_[2] = QPixmap(":/resources/assets/water_tile_destroyed.jpg").scaled(QSize(25, 25));
    tiles_textures_[1] = QPixmap(":/resources/assets/duck_tile.png").scaled(QSize(25, 25));
    tiles_textures_[3] = QPixmap(":/resources/assets/duck_tile_destroyed.png").scaled(QSize(25, 25));

    // preview placement tiles
    tiles_textures_[4] = QPixmap(":/resources/assets/placeable_watertile.jpg").scaled(QSize(25, 25));
    tiles_textures_[5] = QPixmap(":/resources/assets/nonplaceable_watertile.jpg").scaled(QSize(25, 25));
    tiles_textures_[6] = QPixmap(":/resources/assets/nonplaceable_duck_tile.png").scaled(QSize(25, 25));
}

// draw a board // per row, left to right
void BoardView::drawBoard() {
    this->clear();

    /*
    //for checking family count on board
    std::set<DuckFamily*> list = board_->getDuckFamilies();
    int count = 0;
    for(auto* duck : list) std::cout << count++ << std::endl;
    */

    for(int y = 0; y < 10; y++) {
        for(int x = 0; x < 10; x++) {
         int i;

         /**
           * If the preview mode is enabled and a duck is placeable at the cursor,
           * the specified preview texture is loaded. Start and end of the preview tile sequence
           * is dependant on the aforeset previewStartIndex and movableLength. MovableLength gets
           * decremented during the loop to mark the end of the tile preview.
           */
         if(previewMode_ && x+y*10 >= previewStartIndex_ && movableLength_ > 0) i = 4;
         else i = board_->getTileStatus(x + y * 10);

         if (!board_->isPlayerBoard() && i == 1) i = 0;
         QGraphicsPixmapItem *tile = this->addPixmap(tiles_textures_[i]);
         tile->moveBy(27*x, 27*y);
         tile->setFlags(QGraphicsItem::ItemIsSelectable);
         tiles_.at(x + y * 10) = tile;

         if(i == 4) movableLength_--;
        }
    }
}

// shooting on enemy board
void BoardView::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) {
    if(!board_->isPlayerBoard()) {
        for (int i = 0; i < tiles_.size(); i++) {
            if (tiles_[i]->sceneBoundingRect().contains(event->scenePos())) {
                if(board_->shootable(i)) board_->shoot(i);
                tiles_[i]->setSelected(false);
            }
        }
        drawBoard();
    // starting the previewMode to move ducks on players board
    } else {
            for (int i = 0; i < tiles_.size(); i++) {
                if (tiles_[i]->sceneBoundingRect().contains(event->scenePos())) {
                    if(board_->getTileStatus(i) == 1) {
                        movableLength_ = board_->getLengthAtTile(i);
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
                if(board_->isPlaceable(i, length)) {
                    previewStartIndex_ = i;
                    drawBoard();
                    movableLength_ = length;    // resets movableLength as it gets decremented while drawing
                }
            }
        }
    }
}

// receiver slot for signal from the player setup to place a family
void BoardView::receiveFamily(int length) {
    board_->placeRandomly(length);
    drawBoard();
}
