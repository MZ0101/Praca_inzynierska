#include "LineEdit.h"

LineEdit::LineEdit(QWidget* parent) : QLineEdit(parent)
{
    this->setFixedSize(QSize(100, 25));
    this->setMaxLength(3);
    this->setAlignment(Qt::AlignCenter);
}
LineEdit::~LineEdit()
{

}