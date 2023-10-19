#include "Box_for_1_series.h"

Box_for_1_series::Box_for_1_series(QWidget* parent, QString title) :QGroupBox(parent)
{
	this->setTitle(title);
	this->setFocusPolicy(Qt::StrongFocus);
	this->main_group = new QVBoxLayout();

	QString nazwy[3]{ "Width (x):", "Height (y):", "Picture number (z):" };
	this->setAlignment(Qt::AlignCenter);
	this->edit = new LineEdit[3];
	this->group = new QHBoxLayout[3];
	this->label = new Label[3];

	for (size_t i{ 0 }; i < 3; i++)
	{

		this->label[i].setFixedSize(QSize(120, 30));
		this->label[i].setText(nazwy[i]);
		this->edit[i].setInputMask("");
		this->edit[i].setText(QString::number(i));
		this->edit[i].setFixedSize(QSize(100, 25));
		this->edit[i].setMaxLength(3);
		this->edit[i].setAlignment(Qt::AlignCenter);

		this->group[i].addWidget(&this->label[i]);
		this->group[i].addWidget(&this->edit[i]);
		this->main_group->addLayout(&this->group[i]);
	}

	
	this->setLayout(this->main_group);
	this->edit[currentLineEdit].setFocus();

}

void Box_for_1_series::mousePressEvent(QMouseEvent* evet)
{
	this->edit[currentLineEdit].setFocus();
}

void Box_for_1_series::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Up)
	{
		this->UpFocus();
	}
	else if (event->key() == Qt::Key_Down)
	{
		this->DownFocus();
	}
}

void Box_for_1_series::UpFocus()
{
	if (currentLineEdit > 0)
	{
		this->currentLineEdit--;
	}
	else
	{
		this->currentLineEdit = 2;
	}

	this->edit[currentLineEdit].setFocus();
}

void Box_for_1_series::DownFocus()
{
	if (currentLineEdit < 2)
	{
		this->currentLineEdit++;
	}
	else
	{
		this->currentLineEdit = 0;
	}

	this->edit[currentLineEdit].setFocus();

}

Box_for_1_series::~Box_for_1_series()
{
	delete[] label;
	delete[] edit;
	delete[] group;
	delete main_group;
}