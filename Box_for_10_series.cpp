#include "Box_for_10_series.h"

Box_for_10_series::Box_for_10_series(QWidget* parent) : QGroupBox(parent)
{
    this->button = new Buttons;
    this->b_vertical = new QVBoxLayout();

    //this->button[0].setText("Wybierz");
    this->button->setText("Mark");

    this->vertical = new QVBoxLayout();
    this->horizontal =  new QHBoxLayout[3];
    
    this->main_horisontal =new QHBoxLayout(this);
    this->setLayout(this->main_horisontal);

    QString e_name[2] = { "Start data:", "Target data:" };
    QString p_name[4] = { "Etykiety", "Width (x)", "Height (y)", "Picture number (z)" };

    for (size_t i{ 0 }; i < 4; i++)
    {
        this->podpisy[i].setText(p_name[i]);
        this->horizontal[0].addWidget(&this->podpisy[i]);
    }

    for (size_t i{ 0 }; i < 2; i++)
    {
        this->etykiety[i].setText(e_name[i]);
        this->horizontal[i + 1].addWidget(&this->etykiety[i]);
       // this->b_vertical->addWidget(this->button);
    }

    for (size_t i{ 0 }; i < 3; i++)
    {
        
        this->horizontal[1].addWidget(&this->begin_labels[i]);
        this->horizontal[2].addWidget(&this->end_labels[i]);
        this->vertical->addLayout(&this->horizontal[i]);
    }
    
    this->main_horisontal->addLayout(this->vertical);
    //this->main_horisontal->addLayout(this->b_vertical);
    this->main_horisontal->addWidget(this->button);

    this->main_horisontal->setAlignment(this->button,Qt::AlignHCenter);
}

Box_for_10_series::~Box_for_10_series()
{
    delete  button;
    delete[] horizontal;
    delete vertical;

    delete b_vertical;
    delete main_horisontal;
}