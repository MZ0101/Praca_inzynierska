#pragma once

#include <QDir>
#include <ctime> 
#include "Box_for_10_series.h"

class Series_10 : public QWidget
{

public:

    Series_10(QWidget *partent = nullptr);
    ~Series_10();
    Box_for_10_series *boxs_data = nullptr;
    QVBoxLayout *verticals = nullptr;
    Buttons *button_for_calculate = nullptr;
    Buttons* button_for_randomize = nullptr;

    QHBoxLayout *horisontal_for_boxs = nullptr;
    QHBoxLayout *horisontal_for_bottom_buttons = nullptr;
    QVBoxLayout vertical_main;

    int button_number{ 0 };

    //int division = { 0 };
    //float average_way = { 0.0 };

    void mark_button(Buttons* button_clicked);
private slots:
    void randomization_of_points();

};

