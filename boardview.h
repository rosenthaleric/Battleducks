#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>

#include "enemy.h"
#include "board.h"

class BoardView : public QGraphicsScene
{
    Q_OBJECT
public:
    BoardView(QObject *parent = 0, Board* board = 0);
    void drawBoard();
    void setEnemy(Enemy* enemy);
    void enemyAction(bool);

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
    Enemy* enemy_;

signals:
    void returnFamily(int length);
    void duckSound();
    void cpu_lost();
    void player_lost();

public slots:
    void receiveFamily(int length);
    void win();
    void lose();
    void start();
};

#endif // BOARDVIEW_H
