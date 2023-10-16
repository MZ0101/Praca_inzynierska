#include "View.h"

View::View(QWidget* parent) : QGraphicsView(parent)
{
    this->setRenderHint(QPainter::Antialiasing);
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    this->setDragMode(QGraphicsView::ScrollHandDrag);
    this->setInteractive(true);
    this->FullViewportUpdate;

    this->setAlignment(Qt::AlignCenter);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   // this->scenea = new QGraphicsScene(this);
    this->scene_v.setSceneRect(0, 0, 800, 800);
    this->setScene(&this->scene_v);

    this->setStyleSheet("background-color: white; border : 1px solid black;");

    this->setFixedSize(1000,800);
}

void View::wheelEvent(QWheelEvent *while_event)
{
    QPointF mouse_pos = while_event->position();

    QPointF mouse_on_scene_pos = mapToScene(mouse_pos.toPoint());

    qreal scale = (while_event->angleDelta().y() < 0) ? 0.9 : 1.1; // operator warunkowy ternarny konstrukacja (warunek) ? prawda:fausz TEN PYTAJNIK WAZNY

    qreal new_scale = this->transform().m11() * scale; // m11 odnosi sie do transforamacji macierzy 

    if (new_scale < scale_min)
    {
        new_scale = scale_min;
    }
    else if (new_scale > scale_max)
    {
        new_scale = scale_max;
    }

    this->setTransform(QTransform().scale(new_scale, new_scale), false);

    QPointF new_mouse_pos_on_scene = mapToScene(mouse_pos.toPoint()) - mouse_on_scene_pos;

    this->horizontalScrollBar()->setValue(this->horizontalScrollBar()->value() + new_mouse_pos_on_scene.x());
    this->verticalScrollBar()->setValue(this->verticalScrollBar()->value() + new_mouse_pos_on_scene.y());
    while_event->accept();
}