#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QPixmap>

#include "board.h"
#include "boardView.h"

/**
 * Responsible for drawing the tiles of a board to a given scene.
 * TODO callbacks and Signals
 */

BoardView::BoardView(QObject *parent) : QGraphicsScene(parent) {
    //scene_ = scene;
    board_ = Board();
    tiles_ = std::vector<QGraphicsPixmapItem*>(100);
    tiles_textures_ = std::vector<QPixmap>(4);
    tiles_textures_[0] = QPixmap(":/resources/assets/water_tile.jpg").scaled(QSize(25, 25));
    tiles_textures_[2] = QPixmap(":/resources/assets/water_tile_destroyed.jpg").scaled(QSize(25, 25));
}

// draw a board // per row, left to right
void BoardView::drawBoard() {
    this->clear();
    for(int y = 0; y < 10; y++) {
        for(int x = 0; x < 10; x++) {
         int i = board_.getTileStatus(x, y);
         QGraphicsPixmapItem *tile = this->addPixmap(tiles_textures_[i]);
         tile->moveBy(27*x, 27*y);
         tile->setFlags(QGraphicsItem::ItemIsSelectable);
         tiles_.at(x + y * 10) = tile;
        }
    }
}

void BoardView::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    for (int i = 0; i < tiles_.size(); i++) {
        if (tiles_[i]->isSelected()) {
            board_.shoot(i);
            tiles_[i]->setSelected(false);
        }
    }
    drawBoard();
}
