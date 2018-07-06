#ifndef SETUPVIEW_H
#define SETUPVIEW_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include "setupitem.h"
#include "board.h"

class SetupView : public QGraphicsScene
{
    Q_OBJECT
public:
    SetupView(QObject *parent = 0);
    void drawSetup();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

private:
    QGraphicsScene* scene_;
    std::vector<SetupItem*> items_;
    std::vector<QPixmap> setup_textures_;
};

#endif // SETUPVIEW_H
