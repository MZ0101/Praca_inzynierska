#pragma once

#include "Label.h"
#include "Buttons.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include "LineEdit.h"


class Box_for_10_series : public QGroupBox
{
    
public:
    Box_for_10_series(QWidget* parent = nullptr);
    ~Box_for_10_series();

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