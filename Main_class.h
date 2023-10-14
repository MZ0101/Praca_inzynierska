#pragma once

#include "Series_1.h"
#include "Series_10.h"
#include "Result_10.h"
#include "Mark.h"
#include "A_01.h"
#include "Control_Widget.h"

#include <QScreen>
#include <QMessageBox>
#include <QMainWindow>
#include <QApplication>

class Main_class : public QObject
{
    Q_OBJECT

public:
    Main_class(QObject* parent = nullptr);
    ~Main_class();

    WidgetsControl* control_widget = nullptr;

    Series_1* series_1 = nullptr;
    Series_10* series_10 = nullptr;
    Mark* mark = nullptr;

    Result_1* result_1 = nullptr;
    Result_10* result_10 = nullptr;
    Begin_Widget* widget = nullptr;
    QVBoxLayout* vertical = nullptr;

    int begin[3] = { 0,0,0 };
    int end[3] = { 0,0,0 };
    int division = { 0 };
    float average_way = { 0.0 };

    QString result_path;


    void check_checkbox();
    void obliczenia();
    void screen(QWidget* widget);

    void mark_connect();
    void result_1_create();
    void result_10_create();
    void series_1_ch();
    void series_10_ch();
 
   // void for_control_widget_method();

    template <class current_algorithm>
    void common_calculations(current_algorithm* execute)
    {
        this->division = 0;
        this->average_way = 0;
       // this->control_widget->method_label_box->setText("Method: " + this->control_widget->method_label[this->control_widget->current_method]);
       // this->control_widget->box_for_calculation->show();
        if (this->series_10)
        {
            this->result_path += "//Series_";
            this->result_10->files_path = this->result_path;
            qDebug() << this->result_path;
           // this->control_widget->files_path.emplace(this->control_widget->current_method,this->result_path);
            this->result_10->image_remove();
            this->result_10->current_series = 0;
            this->result_10->max_series = -1;
            float value{ 0.0 };

            for (size_t i{ 0 }; i < 10; i++)
            {
                for (size_t j{ 0 }; j < 3; j++)
                {
                    this->begin[j] = this->series_10->boxs_data[i].begin_labels[j].text().toInt();
                    this->end[j] = this->series_10->boxs_data[i].end_labels[j].text().toInt();
                }

                if (execute->Reload(this->begin, this->end))
                {
                    value = 0.0;

                    execute->result_path = this->result_path + QString::number(i);
                    execute->Executive();

                    value = execute->nodes[this->end[2]][this->end[0]][this->end[1]].real;
                    this->result_10->max_series++;
                    this->result_10->series_array[this->result_10->max_series] = i;
                    this->result_10->series_labels[this->result_10->max_series].setText("Series " + QString::number(i + 1) + " : " + QString::number(value));
                    this->result_10->series_labels[this->result_10->max_series].setStyleSheet("background-color: white; border : 2px solid grey;");
                    this->division++;
                    this->average_way += value;

                }
            }

            if (this->division > 0)
            {
                this->average_way = this->average_way / this->division;
                this->result_10->series_labels[10].setText("Average: " + QString::number(this->average_way));
                this->result_10->series_labels[10].setStyleSheet("background-color: white; border : 2px solid blue;");
                this->result_10->image_change();
            }
            else
            {
                this->result_10->series_labels[10].setText("EMPTY");
                this->result_10->series_labels[10].setStyleSheet("background-color: white; border : 2px solid red;");
                this->result_10->buttons[0].setEnabled(false);
                this->result_10->buttons[1].setEnabled(false);
            }
        }
        else
        {
            this->result_1->files_path = this->result_path;
          //  this->control_widget->files_path.emplace(this->control_widget->current_method, this->result_path);
            this->result_1->image_reamove();

            for (size_t i{ 0 }; i < 3; i++)
            {
                this->begin[i] = this->series_1->right_box.edit[i].text().toInt();
                this->end[i] = this->series_1->left_box.edit[i].text().toInt();
            }

            if (execute->Reload(this->begin, this->end))
            {
                execute->result_path = this->result_path;
                execute->Executive();
               
                this->average_way = execute->nodes[this->end[2]][this->end[0]][this->end[1]].real;
            }
            
            this->result_1->image_reload();
        }
    }
};