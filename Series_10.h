#pragma once

#include "Box_for_10_series.h"

class Series_10 : public QWidget
{

public:

    Series_10(QWidget *partent = nullptr);
    ~Series_10();
    Box_for_10_series *boxs_data = nullptr;
    QVBoxLayout *verticals = nullptr;
    Buttons *button_clicked = nullptr;

    QHBoxLayout *horisontal_mian = nullptr;
    QVBoxLayout vertical_main;

    int button_number{ 0 };
    int begin[3] = { 199,80,0 };
    int end[3] = { 80,199,2 };
    int division = { 0 };
    float average_way = { 0.0 };

private:
    void mark_button(Buttons* button_clicked);
};

