#ifndef ENEMY_H
#define ENEMY_H
#include "board.h"
#include <QObject>

class BoardView;
class Enemy: public QObject
{
    Q_OBJECT
public:
    Enemy(QObject* parent = 0, BoardView* bw = 0, Board* b = 0);

public slots:
    void shoot();

private:
    int last_shot_;
    Board* player_board_;
    BoardView* bw_;
};
#endif // ENEMY_H
