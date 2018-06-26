#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>

class BoardView
{
public:
    BoardView(QGraphicsScene* scene);

    void drawBoard();

private:
    QGraphicsScene* scene_;
    QPixmap water_tile_;
};

#endif // BOARDVIEW_H
