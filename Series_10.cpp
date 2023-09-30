#include "Series_10.h"
Series_10::Series_10(QWidget* parent) : QWidget(parent)
{
    this->boxs_data = new Pudelko_dane[10];
    this->horisontal_mian = new QHBoxLayout();
    this->horisontal_mian->setAlignment(Qt::AlignCenter);
    //this->vertical_main = new QVBoxLayout();

    this->verticals = new QVBoxLayout[2];
    this->button_clicked = new Buttons();

    this->button_clicked->setText("Calculate");
    this->button_clicked->setFixedWidth(200);
    this->button_clicked->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    for (size_t i{ 0 }; i < 10; i++)
    {
        if (i < 5)
        {
            this->verticals[0].addWidget(&this->boxs_data[i]);
        }
        else
        {
            this->verticals[1].addWidget(&this->boxs_data[i]);
        }

        QObject::connect(this->boxs_data[i].button, &QPushButton::clicked, [this, i]() {Series_10::zaznaczanie_button(this->boxs_data[i].button); });

    }

    this->horisontal_mian->addLayout(&this->verticals[0]);
    this->horisontal_mian->addLayout(&this->verticals[1]);

    this->vertical_main.addLayout(this->horisontal_mian);
    this->vertical_main.addWidget(this->button_clicked);
    this->vertical_main.setAlignment(this->button_clicked, Qt::AlignHCenter);

  
    this->setLayout(&this->vertical_main);
}

void Series_10::zaznaczanie_button(Buttons* button_clicked)
{
    this->hide();
    for (size_t i{ 0 }; i < 10; i++)
    {
        if (button_clicked == this->boxs_data[i].button)
        {
            this->button_number = i;
            break;
        }
    }
}

Series_10::~Series_10()
{
	delete[] boxs_data;
	delete button_clicked;
	delete[] verticals;
    delete horisontal_mian;

}