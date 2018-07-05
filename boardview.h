#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>

#include "board.h"

class BoardView : public QGraphicsScene
{
    Q_OBJECT
public:
    BoardView(QObject *parent = 0);
    void drawBoard();

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);

private:
    QGraphicsScene* scene_;
    Board board_;
    std::vector<QPixmap> tiles_textures_;
    std::vector<QGraphicsPixmapItem*> tiles_;
};

#endif // BOARDVIEW_H
