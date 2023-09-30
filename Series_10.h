#pragma once

#include "Pudelko_dane.h"

class Series_10 : public QWidget
{

public:

    Series_10(QWidget *partent = nullptr);
    ~Series_10();
    Pudelko_dane *boxs_data = nullptr;
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
    void zaznaczanie_button(Buttons* button_clicked);
    //void obliczenia();
};

