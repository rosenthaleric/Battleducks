#ifndef SETUPITEM_H
#define SETUPITEM_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QPixmap>

class SetupItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    SetupItem(int length, QPixmap texture, QObject *parent = 0);
    int getLength();
    void set(bool isSet);
    bool isSet();

private:
    QGraphicsScene* scene_;
    int length_;
    bool is_set_;
};

#endif // SETUPITEM_H
