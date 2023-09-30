
#include "Buttons.h"


Buttons::Buttons() : QPushButton()
{
    this->setFixedSize(QSize(100, 25));
    // this->setStyleSheet("background-color: blue; color: white; border: 1px solid black;");
    // this->setFont(QFont("Arial", 12));
}
Buttons::Buttons(QWidget* parent) : QPushButton(parent)
{
    this->setFixedSize(QSize(100, 25));
    // this->setStyleSheet("background-color: black; color: white; border: 1px solid black;");
   //  this->setFont(QFont("Arial", 12));
}

Buttons::~Buttons()
{
}