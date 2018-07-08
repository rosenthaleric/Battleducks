#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QPixmap>
#include <QList>
#include <iostream>
#include "setupitem.h"
#include "setupview.h"
#include "board.h"

/**
 * Scene for displaying the players unset duck families. These are represented by
 * SetupItems (subclassed QGraphicsPixmapItems). SetupItems contain a length attribute
 * so that dragging them onto the board bears information on how big the family is.
 */

SetupView::SetupView(QObject *parent) : QGraphicsScene(parent) {
    items_ = std::vector<SetupItem*>();
    setup_textures_ = std::vector<QPixmap>(4);
    setup_textures_[0] = QPixmap(":/resources/assets/family2x.png").scaled(QSize(40, 40));
    setup_textures_[1] = QPixmap(":/resources/assets/family3x.png").scaled(QSize(40, 40));
    setup_textures_[2] = QPixmap(":/resources/assets/family4x.png").scaled(QSize(40, 40));
    setup_textures_[3] = QPixmap(":/resources/assets/family5x.png").scaled(QSize(40, 40));

    int index = 0;
    for(int i = 0; i < 10; i++) {
        if(i < 4) index = 0;
        else if(i < 7) index = 1;
        else if(i < 9) index = 2;
        else index = 3;
        SetupItem* item = new SetupItem(index+2, setup_textures_[index], this);
        items_.push_back(item);
    }
}

// fully draws the setup upon first initialization
void SetupView::drawSetup() {
    int i = 0;
    for(int y = 0; y < 2; y++) {
        for(int x = 0; x < 5; x++) {
            if(!items_[i]->isSet()) {
                this->addItem(items_[i]);
                items_[i]->moveBy(40*x, 40*y);
            }
            i++;
        }
    }
}

// updates the setupview, removing every family that is set
void SetupView::updateSetup() {
    int i = 0;
    QList<QGraphicsItem*> scene_items = this->items();  // get all items that are part of the scene
    for(int y = 0; y < 2; y++) {
        for(int x = 0; x < 5; x++) {
            // if item is already set on board, remove it from the setup-scene
            // before removing, iterate through scene_items to check if it already has been removed from the scene
            if(items_[i]->isSet()) {
                for (auto *item : scene_items) if(item == items_[i]) this->removeItem(items_[i]);
            }
            i++;
        }
    }
}

/**
 * handles double click on a setup item and fires a signal to boardview to randomly place
 * a duck family of specified length on its board. the setup item is then set to be "set"
 * and gets hidden from the setup view by calling updateView()
 */
void SetupView::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) {
    for (int i = 0; i < items_.size(); i++) {
        // check for mousepos/itempos and whether item has already been set on the board
        if (items_[i]->sceneBoundingRect().contains(event->scenePos()) && !items_[i]->isSet()) {
            emit sendFamily(items_[i]->getLength());    // firing signal to boardView
            items_.at(i)->set(true);
            updateSetup();
            return;
        }
    }
}

/*
 * receiver SLOT for signal from boardview, taking set duckfamily off
 * the board and back to setupView
 */
void SetupView::retakeFamily(int length) {
    for (auto* item : items_) {
        if(item->isSet() && item->getLength() == length) {
            item->set(false);
            this->addItem(item); // readd item to !SCENE!
            break;
        }
    }
    updateSetup();
}
