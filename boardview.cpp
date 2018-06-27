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

BoardView::BoardView(QGraphicsScene* scene) {
    scene_ = scene;
    board_ = Board();
    tiles_ = std::vector<QPixmap>(4);
    tiles_[0] = QPixmap(":/resources/assets/water_tile.jpg").scaled(QSize(25, 25));
}

// draw an empty board // per row, left to right
void BoardView::drawBoard() {
    for(int y = 0; y < 10; y++) {
        for(int x = 0; x < 10; x++) {
         int i = board_.getTileStatus(y, x);
         QGraphicsPixmapItem *tile = scene_->addPixmap(tiles_[i]);
         tile->moveBy(27*x, 27*y);
        }
    }
}
