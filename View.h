#pragma once
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QScrollBar>
#include <QWheelEvent>
#include <QGraphicsPixmapItem>

class View :
    public QGraphicsView
{
public: 
    View(QWidget* parent = nullptr);
    ~View() {};

    const qreal scale_min = 0.5;
    const qreal scale_max = 4.0;
    QGraphicsScene scene_v;

    void wheelEvent(QWheelEvent*);
};