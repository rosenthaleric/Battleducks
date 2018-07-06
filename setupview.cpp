#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QPixmap>
#include "setupitem.h"
#include "setupview.h"
#include "board.h"

/**
 * Scene for displaying the players unset duck families. These are represented by
 * SetupItems (subclassed QGraphicsPixmapItems). SetupItems contain a length attribute
 * so that dragging them onto the board bears information on how big the family is.
 */

SetupView::SetupView(QObject *parent) : QGraphicsScene(parent) {
    items_ = std::vector<SetupItem*>(10);
    setup_textures_ = std::vector<QPixmap>(4);
    setup_textures_[0] = QPixmap(":/resources/assets/family2x.png").scaled(QSize(40, 40));
    setup_textures_[1] = QPixmap(":/resources/assets/family3x.png").scaled(QSize(40, 40));
    setup_textures_[2] = QPixmap(":/resources/assets/family4x.png").scaled(QSize(40, 40));
    setup_textures_[3] = QPixmap(":/resources/assets/family5x.png").scaled(QSize(40, 40));
}


void SetupView::drawSetup() {
    this->clear();
    int i = 0;
    int index;
    for(int y = 0; y < 2; y++) {
        for(int x = 0; x < 5; x++) {
            if(i < 4) index = 0;
            else if(i < 7) index = 1;
            else if(i < 9) index = 2;
            else index = 3;

            SetupItem* item = new SetupItem(index+2, setup_textures_[index], this);
            this->addItem(item);
            item->moveBy(40*x, 40*y);
            items_.at(i) = item;
            i++;
        }
    }
}

void SetupView::mousePressEvent(QGraphicsSceneMouseEvent* event) {}
