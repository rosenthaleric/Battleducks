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
    void updateSetup();
    void reset();

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);

private:
    QGraphicsScene* scene_;
    std::vector<SetupItem*> items_;
    std::vector<QPixmap> setup_textures_;

signals:
    void sendFamily(int length);

public slots:
    void retakeFamily(int length);
};

#endif // SETUPVIEW_H
