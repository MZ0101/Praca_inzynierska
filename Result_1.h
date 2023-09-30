#pragma once

#include "Buttons.h"
#include "Pudelko.h"
#include "View.h"

#include <QDir>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QImage>

class Result_1 : public QWidget
{
    Q_OBJECT

public:
    Result_1(QWidget* parent = nullptr, QString path = { "Result_1//Result_D" });
    ~Result_1() {};

    QVBoxLayout main_layout;

    QString files_path = { "Result_1//Result_D" };
    QDir dir;
    Buttons buttons[4];
    View image_view;
    QStringList files_list;

    QGraphicsScene *scene = nullptr;
    QGraphicsPixmapItem *pixmapItem = nullptr;
    Label image_name;
    Label result;
  
    QHBoxLayout layout_on_result;
    QHBoxLayout hlayout;
    QHBoxLayout main_hlayout;

    double scaled_image{ 800.0 };
    QImage image;
    int current_image_index{ 0 };
    int max_image_index{ 0 };

    inline void processing();
    void image_reload();
    void if_empty();
    void image_reamove();

protected:
    bool event(QEvent* event) override;
    void end();
    void begin();
    void previous();
    void another();
};
