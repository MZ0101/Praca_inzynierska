#include "Glowna_klasa.h"

Glowna_klasa::Glowna_klasa(QObject* parent) : QObject(parent)
{
    this->control_widget = new WidgetsControl();
 
    QObject::connect(&this->control_widget->buttons[0], &QPushButton::clicked, [&]() {

        this->screen(this->control_widget);

        });

    QObject::connect(&this->control_widget->buttons[1], &QPushButton::clicked, [&]() {

        this->screen(this->control_widget);

        });

    QObject::connect(&this->control_widget->begin_widget->button_1, &QPushButton::clicked, this, &Glowna_klasa::check_checkbox);
   // QObject::connect(&this->control_widget->buttons_box[0], &QPushButton::clicked, this, &Glowna_klasa::check_checkbox);

    this->screen(this->control_widget);
    this->control_widget->show();

}

void Glowna_klasa::screen(QWidget* widget)
{
    widget->adjustSize();
    QScreen* primaryScreen = QGuiApplication::primaryScreen();

    QRect screenRect = primaryScreen->geometry();
    //qDebug() << screenRect.width() << "::::" << screenRect.height();
    int screenWidth = screenRect.width();
    int screenHeight = screenRect.height();

    widget->move((screenWidth - widget->width()) / 2, (screenHeight - widget->height()) / 2);
}

void Glowna_klasa::check_checkbox()
{
    this->control_widget->buttons[0].setEnabled(true);
    this->control_widget->buttons[1].setEnabled(false);
  
    if (this->mark == nullptr)
    {
        this->mark = new Zaznaczanie();
        QObject::connect(this->mark->button, &QPushButton::clicked, this, &Glowna_klasa::mark_connect);
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

void Glowna_klasa::obliczenia()
{
   
    if (this->control_widget->begin_widget->check_2[0].isChecked())
    {
        this->way_calculation = "//Result_D";
     //   this->control_widget->current_method = 0;
        A_01* wykonanie = new A_01;
        this->common_calculations(wykonanie);
        delete wykonanie;
    }
    else if (this->control_widget->begin_widget->check_2[1].isChecked())
    {
        this->way_calculation = "//Result_T";
      //  this->control_widget->current_method = 1;
        A_02* wykonanie = new A_02;
        this->common_calculations(wykonanie);
        delete wykonanie;
    }

    else if (this->control_widget->begin_widget->check_2[2].isChecked())
    {
        this->way_calculation = "//Result_E";
      //  this->control_widget->current_method = 2;
        A_03* wykonanie = new A_03;
        this->common_calculations(wykonanie);
        delete wykonanie;
    }
   
}

void Glowna_klasa::series_1_ch()
{
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
        this->control_widget->buttons[0].setEnabled(true);
        

        QObject::connect(&this->series_1->buttons[0], &QPushButton::clicked, this, [this]() {

            this->control_widget->hide();
            this->mark->show();

            });

        QObject::connect(&this->series_1->buttons[1], &QPushButton::clicked, this, &Glowna_klasa::result_1_create);

    }

    this->control_widget->widget_array[1] = this->series_1;
}

void Glowna_klasa::series_10_ch()
{
    
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
        this->control_widget->buttons[0].setEnabled(true);


        for (size_t i{ 0 }; i < 10; i++)
        {
            QObject::connect(this->series_10->boxs_data[i].button, &QPushButton::clicked, [this]() {

                this->control_widget->hide();
                this->mark->show();
                });
        }

        QObject::connect(this->series_10->button_clicked, &QPushButton::clicked, this, &Glowna_klasa::result_10_create);
    }
   
    this->control_widget->widget_array[1] = this->series_10;
}

void Glowna_klasa::result_1_create()
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
    this->obliczenia();
  
    this->series_1->hide();
    this->result_1->show();
    this->screen(this->control_widget);

    this->result_1->result.setText("Result: " + QString::number(this->average_way));
}

void Glowna_klasa::result_10_create()
{
    if (this->result_10 == nullptr)
    {
        this->result_10 = new Result_10();
        this->control_widget->widget_array[2] = this->result_10;
       // this->result_path += "//Seria_";
    }

    this->control_widget->current_widget++;
    this->control_widget->vertical->removeWidget(this->control_widget->widget_array[1]);
    this->control_widget->vertical->addWidget(this->control_widget->widget_array[2]);

    this->obliczenia();
    

    this->series_10->hide();
    this->result_10->show();

    this->screen(this->control_widget);
}

void Glowna_klasa::mark_connect()
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

//void Glowna_klasa::for_control_widget_method()
//{
//
//    if (qobject_cast<Buttons*>(sender()) == &this->control_widget->buttons_box[1])
//    {
//        this->control_widget->previous_method();
//    }
//    else
//    {
//        this->control_widget->another_method();
//    }
//
//}

Glowna_klasa::~Glowna_klasa()
{
    if (mark) delete mark;
    if (series_1) delete series_1;
    if (result_1) delete result_1;
    if (series_10) delete series_10;
    if (result_10) delete result_10;
    //if (widget) delete widget;

    if (control_widget) delete control_widget;
}