#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>

#include "board.h"

class BoardView
{
public:
    BoardView(QGraphicsScene* scene);
    void drawBoard();

private:
    QGraphicsScene* scene_;
    Board board_;
    std::vector<QPixmap> tiles_;
};

#endif // BOARDVIEW_H
