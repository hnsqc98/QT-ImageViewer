#ifndef MYPIXMAPITEM_H
#define MYPIXMAPITEM_H

#include <QObject>
#include<QGraphicsPixmapItem>
#include<QGraphicsSceneMouseEvent>
#include<QGraphicsSceneWheelEvent>

class MyPixmapItem : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit MyPixmapItem(QGraphicsPixmapItem *parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void wheelEvent(QGraphicsSceneWheelEvent *event);
    void reset();

signals:

public slots:
};

#endif // MYPIXMAPITEM_H
