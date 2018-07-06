#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include "setupitem.h"

/**
 * Subclassed QGraphicsPixmapItem in the SetupView - Scene, representing a
 * settable duck fammily with a length.
 */

SetupItem::SetupItem(int length, QPixmap texture, QObject *parent)
    :  QObject(parent),
       length_(length)
{
    this->setPixmap(texture);
}

int SetupItem::getLength() {
    return length_;
}

bool isSet() {
    return isSet();
}
