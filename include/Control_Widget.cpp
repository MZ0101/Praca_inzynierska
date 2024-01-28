#include "Control_Widget.h"

Begin_Widget::Begin_Widget(QWidget* parent) : QWidget(parent)
{

	QString text[] = { "One Series: ", "Ten Series: " };
	QString text_heuristic[] = { "Dijkstra Algorithm ", "A* (A start) Algorithm ", "Euclidean Distance" };

	for (size_t i{ 0 }; i < 2; i++)
	{
		this->check_1[i].setText(text[i]);
		this->vertical_1[0].addWidget(&this->check_1[i]);
		QObject::connect(&this->check_1[i], &QCheckBox::clicked, this, &Begin_Widget::currentCheckBox_1);
	}

	for (size_t i{ 0 }; i < 3; i++) 
	{
		this->check_2[i].setText(text_heuristic[i]);
		this->vertical_1[1].addWidget(&this->check_2[i]);
		QObject::connect(&this->check_2[i], &QCheckBox::clicked, this, &Begin_Widget::currentCheckBox_2);

	}

	this->button_1.setText("Select");

	this->horisontal_box_1.addWidget(&this->button_1);
	this->horisontal_box_1.addLayout(&this->vertical_1[0]);
	this->horisontal_box_1.addLayout(&this->vertical_1[1]);

	this->main_layout.addLayout(&this->horisontal_box_1);

	this->check_1[0].setChecked(true);
	this->check_2[0].setChecked(true);

	this->setLayout(&this->main_layout);
}

void Begin_Widget::currentCheckBox_1() 
{
	QCheckBox* current_Box = qobject_cast<QCheckBox*>(sender());

	int n = sizeof(this->check_1) / sizeof(this->check_1[0]);
	

	for (int i = 0; i < n; i++)
	{
		this->check_1[i].setChecked(false);
	}
	
	current_Box->setChecked(true);

}

void Begin_Widget::currentCheckBox_2() 
{
	QCheckBox* current_Box = qobject_cast<QCheckBox*>(sender());

	int n = sizeof(this->check_2) / sizeof(this->check_2[0]);


	for (int i = 0; i < n; i++)
	{
		this->check_2[i].setChecked(false);
	}

	current_Box->setChecked(true);
}

WidgetsControl::WidgetsControl()
{
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	this->vertical = new QVBoxLayout(this);

	this->begin_widget = new Begin_Widget(this);
	this->horisontal = new QHBoxLayout(this);

	this->buttons[0].setText("Previous");
	this->buttons[1].setText("Another");
	
	this->horisontal->addWidget(&this->buttons[0]);
	this->horisontal->addWidget(&this->buttons[1]);
	
	QObject::connect(&this->buttons[0], &QPushButton::clicked, this, &WidgetsControl::previous_widget);
	QObject::connect(&this->buttons[1], &QPushButton::clicked, this, &WidgetsControl::another_widget);

	
	this->horisontal->setAlignment(Qt::AlignLeft);
	this->vertical->addLayout(this->horisontal);

	this->setLayout(this->vertical);

	this->widget_array[0] = this->begin_widget;
	this->vertical->addWidget(this->widget_array[0]);
	this->setWindowFlags(this->windowFlags() & ~Qt::WindowMaximizeButtonHint);
}

void WidgetsControl::previous_widget()
{
	if (this->current_widget > 0)
	{
		this->widget_array[this->current_widget]->hide();
		this->vertical->removeWidget(this->widget_array[this->current_widget]);
		this->current_widget--;

		this->vertical->addWidget(this->widget_array[this->current_widget]);
		this->widget_array[this->current_widget]->show();
	}
}

void WidgetsControl::another_widget()
{
	if (this->current_widget < 2  && this->widget_array[this->current_widget + 1] != nullptr)
	{
		this->widget_array[this->current_widget]->hide();
		this->vertical->removeWidget(this->widget_array[this->current_widget]);
		this->current_widget++;

		this->vertical->addWidget(this->widget_array[this->current_widget]);
		this->widget_array[this->current_widget]->show();
	}
}
