#pragma once

#include <QFile>
#include <QDir>

#include "Buttons.h"
#include "Pudelko.h"

class Series_1 : public QWidget
{
    Q_OBJECT

public:
    Series_1(QWidget *parent = nullptr);
    ~Series_1() {};

      Buttons buttons[2];
      QHBoxLayout box_group;
      QHBoxLayout button_group;
      Pudelko right_box;
      Pudelko left_box;

      QString path = { "Result_1//Result_D" };

      QVBoxLayout *main_layout = nullptr;

    void removed_files();
    

};
