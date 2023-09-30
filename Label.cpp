#include "Label.h"

Label::Label(QWidget* parent) : QLabel(parent)
{
    this->setAlignment(Qt::AlignCenter);
}

void Label::style_view(QString name)
{
    this->setText("Image name: " + name);
    this->setAlignment(Qt::AlignCenter);
    this->setFixedSize(225, 25);
    this->setStyleSheet("background-color: white; border : 1px solid black;");
    this->setFont(QFont("Arial", 11));

}


Label::~Label()
{

}