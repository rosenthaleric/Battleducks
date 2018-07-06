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
       length_(length),
       is_set_(false)
{
    this->setPixmap(texture);
}

int SetupItem::getLength() {
    return length_;
}

void SetupItem::set(bool b) {
    is_set_ = b;
}

bool SetupItem::isSet() {
    return is_set_;
}
