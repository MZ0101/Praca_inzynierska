#pragma once
#include <QGroupBox>
#include "Result_1.h"

class Result_10 :public QWidget  
{
public:
    Result_10(QWidget* parent = nullptr);
    ~Result_10();

    QGroupBox box_on_result;
    Label *series_labels = nullptr;
   
    QVBoxLayout vertical;

    Buttons *buttons = nullptr;
   
    QString files_path = { "Result_10//Result_D//Seria_" };

    
    QHBoxLayout *main_layout = nullptr;
    QHBoxLayout buttons_layout;
    Result_1 *main_result = nullptr;
  

    int current_series{ 0 };
    int max_series{ -1 };
    int series_array[9] = {};

public:
    inline void zmiana();
    void image_remove();
protected:
    void previous();
    void andother();

};

