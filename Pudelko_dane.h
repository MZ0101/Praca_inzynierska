#pragma once

#include "Label.h"
#include "Buttons.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include "LineEdit.h"


class Pudelko_dane : public QGroupBox
{
    
public:
    Pudelko_dane(QWidget* parent = nullptr);
    ~Pudelko_dane();

    Buttons* button = nullptr;
   
    Label etykiety[2];
    Label podpisy[4];
    LineEdit begin_labels[3];
    LineEdit end_labels[3];

    QHBoxLayout *horizontal = nullptr;

    QHBoxLayout* main_horisontal = nullptr;
    QVBoxLayout* vertical = nullptr;
    QVBoxLayout* b_vertical = nullptr;
   


};

