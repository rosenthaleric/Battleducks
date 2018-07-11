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
    BoardView(QObject *parent = 0, Board* board = 0);
    void drawBoard();

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

private:
    QGraphicsScene* scene_;
    Board* board_;
    std::vector<QPixmap> tiles_textures_;
    std::vector<QGraphicsPixmapItem*> tiles_;

    bool previewMode_;
    bool placeablePreview_;
    int movableLength_;
    int previewStartIndex_;
    int oldDuckIndex_;
    int oldDuckLength_;

signals:
    void returnFamily(int length);
    void duckSound();

public slots:
    void receiveFamily(int length);
};

#endif // BOARDVIEW_H
