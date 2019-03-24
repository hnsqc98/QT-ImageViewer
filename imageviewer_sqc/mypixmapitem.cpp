#include "mypixmapitem.h"
#include<QDebug>

MyPixmapItem::MyPixmapItem(QGraphicsPixmapItem *parent) : QGraphicsPixmapItem(parent)
{

}


void MyPixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<"press";
}
void MyPixmapItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    setPos(pos()+mapToParent(event->pos())-mapToParent(event->lastPos()));
    qDebug()<<"move";
}
void MyPixmapItem::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    qDebug()<<"wheel";
    qDebug()<<event->delta();
    double s =scale();
    double percent=0.1;
    if (event->delta()>0)
    {
        s*=(1+percent);
    }
    if (event->delta()<0)
    {
        s*=(1-percent);
    }
    setTransformOriginPoint(boundingRect().width()/2,boundingRect().height()/2);
    setScale(s);
}

void MyPixmapItem::reset()
{
    setPos(0,0);
    setScale(1.0);
}
