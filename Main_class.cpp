#include "Main_class.h"

Main_class::Main_class(QObject* parent) : QObject(parent)
{
    this->control_widget = new WidgetsControl();
 
    QObject::connect(&this->control_widget->buttons[0], &QPushButton::clicked, [&]() {

        this->screen(this->control_widget);

        });

    QObject::connect(&this->control_widget->buttons[1], &QPushButton::clicked, [&]() {

        this->screen(this->control_widget);

        });

    QObject::connect(&this->control_widget->begin_widget->button_1, &QPushButton::clicked, this, &Main_class::check_checkbox);
   // QObject::connect(&this->control_widget->buttons_box[0], &QPushButton::clicked, this, &Glowna_klasa::check_checkbox);

    this->screen(this->control_widget);
    this->control_widget->show();

}

void Main_class::screen(QWidget* widget)
{
    widget->adjustSize();
    QScreen* primaryScreen = QGuiApplication::primaryScreen();

    QRect screenRect = primaryScreen->geometry();

    int screenWidth = screenRect.width();
    int screenHeight = screenRect.height();

    widget->move((screenWidth - widget->width()) / 2, (screenHeight - widget->height()) / 2);
}

void Main_class::check_checkbox()
{
  /*  this->control_widget->buttons[0].setEnabled(true);
    this->control_widget->buttons[1].setEnabled(false);*/
    
    if (!this->mark)
    {
        this->mark = new Mark();
        QObject::connect(this->mark->button, &QPushButton::clicked, this, &Main_class::mark_connect);
        this->screen(this->mark);
    }

    if (this->control_widget->begin_widget->check_1[0].isChecked())
    {
        this->series_1_ch();
    }
    else 
    {
        this->series_10_ch();
    }

    this->control_widget->begin_widget->hide();
    this->control_widget->current_widget++;
    this->control_widget->vertical->removeWidget(this->control_widget->widget_array[0]);
    this->control_widget->vertical->addWidget(this->control_widget->widget_array[1]);
    this->control_widget->widget_array[1]->show();
    this->screen(this->control_widget);

}

void Main_class::series_1_ch()
{
    this->result_path = "Result_1";

    if (this->series_10)
    {
        delete this->series_10;
        if (this->result_10) delete this->result_10;
        this->result_10 = nullptr;
        this->series_10 = nullptr;
        this->control_widget->widget_array[2] = nullptr;
    }

    if (this->series_1 == nullptr)
    {
        this->series_1 = new Series_1();
       // this->control_widget->buttons[0].setEnabled(true);

        QObject::connect(&this->series_1->buttons[0], &QPushButton::clicked, this, [this]() {

            this->control_widget->hide();
            this->mark->show();

            });

        QObject::connect(&this->series_1->buttons[1], &QPushButton::clicked, this, &Main_class::result_1_create);

    }

    this->control_widget->widget_array[1] = this->series_1;
}

void Main_class::series_10_ch()
{
    this->result_path = "Result_10";

    if (this->series_1)
    {
        delete this->series_1;
        if (this->result_1) delete this->result_1;
        this->result_1 = nullptr;
        this->series_1 = nullptr;
        this->control_widget->widget_array[2] = nullptr;
    }

    if (this->series_10 == nullptr)
    {
        this->series_10 = new Series_10();

       // this->control_widget->buttons[0].setEnabled(true);


        for (size_t i{ 0 }; i < 10; i++)
        {
            QObject::connect(this->series_10->boxs_data[i].button, &QPushButton::clicked, [this]() {

                this->control_widget->hide();
                this->mark->show();
                });
        }

        QObject::connect(this->series_10->button_clicked, &QPushButton::clicked, this, &Main_class::result_10_create);
    }
   
    this->control_widget->widget_array[1] = this->series_10;
}

void Main_class::result_1_create()
{

    if (this->result_1 == nullptr)
    {
        this->result_1 = new Result_1();

        this->control_widget->widget_array[2] = this->result_1;
    }

    this->control_widget->current_widget++;
    this->control_widget->vertical->removeWidget(this->control_widget->widget_array[1]);
    this->control_widget->vertical->addWidget(this->control_widget->widget_array[2]);

    //this->result_1->files_path = this->result_path;
    this->calculation();
  
    this->series_1->hide();
    this->result_1->show();
    this->screen(this->control_widget);

    this->result_1->result.setText("Result: " + QString::number(this->average_way));
}

void Main_class::result_10_create()
{

    if (this->result_10 == nullptr)
    {
        this->result_10 = new Result_10();
        this->control_widget->widget_array[2] = this->result_10;
    }

    this->control_widget->current_widget++;
    this->control_widget->vertical->removeWidget(this->control_widget->widget_array[1]);
    this->control_widget->vertical->addWidget(this->control_widget->widget_array[2]);

    
    this->calculation();
   
    this->series_10->hide();
    this->result_10->show();

    this->screen(this->control_widget);
}

void Main_class::calculation()
{
    Algorithm_base* execute = nullptr;

    if (this->control_widget->begin_widget->check_2[0].isChecked())
    {
        //this->result_path += "//Result_D";

        execute = new  Algorithm_base(0); // 0 - means dikstra algorithm
        execute->result_path = this->result_path + "//Result_D";

    }
    else if (this->control_widget->begin_widget->check_2[1].isChecked())
    {
        //this->result_path += "//Result_T";

        execute = new  Algorithm_base(1); // 1 - means the A* algorithm, where sorting is based on the sum of the real value and the Eucleidean distance
        execute->result_path = this->result_path + "//Result_T";
    }

    else if (this->control_widget->begin_widget->check_2[2].isChecked())
    {
        //this->result_path += "//Result_E";

        execute = new  Algorithm_base(2); // 2 - means the A* algorithm, where sorting is based on the Eucleidean distance

        execute->result_path = this->result_path + "//Result_E";
    }

        this->division = 0;
        this->average_way = 0;
       // this->control_widget->method_label_box->setText("Method: " + this->control_widget->method_label[this->control_widget->current_method]);
       // this->control_widget->box_for_calculation->show();
        if (this->series_10)
        {
            //this->result_path += ;
            this->result_10->files_path = execute->result_path + "//Series_";
            qDebug() << this->result_path;
           
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

                    execute->result_path = execute->result_path + "//Series_" + QString::number(i);
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
              /*  this->result_10->buttons[0].setEnabled(false);
                this->result_10->buttons[1].setEnabled(false);*/
            }
        }
        else
        {
            this->result_1->files_path = execute->result_path;
            this->result_1->image_reamove();

            for (size_t i{ 0 }; i < 3; i++)
            {
                this->begin[i] = this->series_1->right_box.edit[i].text().toInt();
                this->end[i] = this->series_1->left_box.edit[i].text().toInt();
            }

            if (execute->Reload(this->begin, this->end))
            {
               // execute->result_path = this->result_path;
                execute->Executive();
               
                this->average_way = execute->nodes[this->end[2]][this->end[0]][this->end[1]].real;
            }
            
            this->result_1->image_reload();
        }

    delete  execute;
}

void Main_class::mark_connect()
{
    if (this->mark->boxs[0].edit[2].text().toInt() > this->mark->boxs[1].edit[2].text().toInt())
    {
        QMessageBox informacja;
        informacja.setWindowTitle("Warning");
        informacja.setText(QString("Begining (z) > End (z)"));
        informacja.setIcon(QMessageBox::Warning);
        informacja.exec();

    }
    else
    {
        this->mark->hide();
        this->control_widget->show();

        if (this->series_1)
        {
            for (size_t i{ 0 }; i < 3; i++)
            {
                this->series_1->left_box.edit[i].setText(this->mark->boxs[1].edit[i].text());
                this->series_1->right_box.edit[i].setText(this->mark->boxs[0].edit[i].text());
            }
        }
        else
        {
            this->series_10->show();

            for (size_t i{ 0 }; i < 3; i++)
            {
                this->series_10->boxs_data[this->series_10->button_number].begin_labels[i].setText(this->mark->boxs[0].edit[i].text());
                this->series_10->boxs_data[this->series_10->button_number].end_labels[i].setText(this->mark->boxs[1].edit[i].text());
            }
        }
    }
}

Main_class::~Main_class()
{
    if (mark) delete mark;
    if (series_1) delete series_1;
    if (result_1) delete result_1;
    if (series_10) delete series_10;
    if (result_10) delete result_10;
   
    if (control_widget) delete control_widget;
}