#include "Control_Widget.h"

Begin_Widget::Begin_Widget(QWidget* parent) : QWidget(parent)
{

	QString text[] = { "One Series: ", "Ten Series: " };
	QString text_heuristic[] = { "Dikstra ", "Total ", "Euklidesowa " };

	for (size_t i{ 0 }; i < 2; i++)
	{
		this->check_1[i].setText(text[i]);
		this->vertical_1[0].addWidget(&this->check_1[i]);
		QObject::connect(&this->check_1[i], &QCheckBox::stateChanged, this, &Begin_Widget::currentCheckBox_1);
	}

	for (size_t i{ 0 }; i < 3; i++) 
	{
		this->check_2[i].setText(text_heuristic[i]);
		this->vertical_1[1].addWidget(&this->check_2[i]);
		QObject::connect(&this->check_2[i], &QCheckBox::stateChanged, this, &Begin_Widget::currentCheckBox_2);

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

void Begin_Widget::currentCheckBox_1() // do poprawy
{
	QCheckBox* current_Box = qobject_cast<QCheckBox*>(sender());

	QObject::disconnect(&this->check_1[0], &QCheckBox::stateChanged, this, &Begin_Widget::currentCheckBox_1);
	QObject::disconnect(&this->check_1[1], &QCheckBox::stateChanged, this, &Begin_Widget::currentCheckBox_1);

	if (current_Box == &this->check_1[0] && this->check_1[1].isChecked())
	{
		this->check_1[0].setChecked(true);
		this->check_1[1].setChecked(false);
	}
	else if (current_Box == &this->check_1[1] && this->check_1[0].isChecked())
	{
		this->check_1[0].setChecked(false);
		this->check_1[1].setChecked(true);
	}
	QObject::connect(&this->check_1[0], &QCheckBox::stateChanged, this, &Begin_Widget::currentCheckBox_1);
	QObject::connect(&this->check_1[1], &QCheckBox::stateChanged, this, &Begin_Widget::currentCheckBox_1);
}

void Begin_Widget::currentCheckBox_2() // to jest te¿ do poprawy 
{
	QCheckBox* current_Box = qobject_cast<QCheckBox*>(sender());

	QObject::disconnect(&this->check_2[0], &QCheckBox::stateChanged, this, &Begin_Widget::currentCheckBox_2);
	QObject::disconnect(&this->check_2[1], &QCheckBox::stateChanged, this, &Begin_Widget::currentCheckBox_2);
	QObject::disconnect(&this->check_2[2], &QCheckBox::stateChanged, this, &Begin_Widget::currentCheckBox_2);


	if (current_Box == &this->check_2[0] && (this->check_2[1].isChecked() || this->check_2[2].isChecked()) )
	{
	
		this->check_2[0].setChecked(true);
		this->check_2[1].setChecked(false);
		this->check_2[2].setChecked(false);

	}
	else if (current_Box == &this->check_2[1] && (this->check_2[0].isChecked() || this->check_2[2].isChecked()))
	{
	
		this->check_2[0].setChecked(false);
		this->check_2[1].setChecked(true);
		this->check_2[2].setChecked(false);
	}

	else if (current_Box == &this->check_2[2] && (this->check_2[0].isChecked() || this->check_2[1].isChecked()))
	{
		this->check_2[0].setChecked(false);
		this->check_2[1].setChecked(false);
		this->check_2[2].setChecked(true);
	}
	else
	{
		current_Box->setChecked(true);
	}


	QObject::connect(&this->check_2[0], &QCheckBox::stateChanged, this, &Begin_Widget::currentCheckBox_2);
	QObject::connect(&this->check_2[1], &QCheckBox::stateChanged, this, &Begin_Widget::currentCheckBox_2);
	QObject::connect(&this->check_2[2], &QCheckBox::stateChanged, this, &Begin_Widget::currentCheckBox_2);

}

WidgetsControl::WidgetsControl()
{
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	this->buttons[0].setText("Previous");
	this->buttons[1].setText("Another");
	this->buttons[0].setEnabled(false);
	this->buttons[1].setEnabled(false);

	this->begin_widget = new Begin_Widget();

	//this->box_for_calculation = new QGroupBox();
	//this->horisontal_box = new QHBoxLayout();
	//this->buttons_box = new Buttons[3];
	//this->method_label_box = new Label();

	///*for (size_t i{ 0 }; i < 3; i++)
	//{
	//	this->horisontal_box->addWidget(&this->begin_widget->check_2[i]);
	//}*/

	// this->buttons_box[0].setText("Calculate");
	// this->horisontal_box->addWidget(&this->buttons_box[0]);
	// this->buttons_box[1].setText("Previous");
	// 
	// this->horisontal_box->addWidget(&this->buttons_box[1]);
	// this->method_label_box->setText("Method: ");
	// this->horisontal_box->addWidget(this->method_label_box);
	// this->buttons_box[2].setText("Another");
	// this->horisontal_box->addWidget(&this->buttons_box[2]);

	// this->box_for_calculation->hide();
	// this->box_for_calculation->setLayout(this->horisontal_box);

	 this->horisontal = new QHBoxLayout();
	
	this->horisontal->addWidget(&this->buttons[0]);
	this->horisontal->addWidget(&this->buttons[1]);
	//this->horisontal->addWidget(this->box_for_calculation);

	QObject::connect(&this->buttons[0], &QPushButton::clicked, this, &WidgetsControl::previous_widget);
	QObject::connect(&this->buttons[1], &QPushButton::clicked, this, &WidgetsControl::another_widget);
	/*QObject::connect(&this->buttons_box[1], &QPushButton::clicked, this, &WidgetsControl::previous_method);
	QObject::connect(&this->buttons_box[2], &QPushButton::clicked, this, &WidgetsControl::another_method);*/

	this->vertical = new QVBoxLayout();

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

		this->buttons[1].setEnabled(true);

		if (this->current_widget == 0) this->buttons[0].setEnabled(false);
		//this->box_for_calculation->hide();
	}
}

void WidgetsControl::another_widget()
{
	if (this->current_widget < 2)
	{
		this->widget_array[this->current_widget]->hide();
		this->vertical->removeWidget(this->widget_array[this->current_widget]);
		this->current_widget++;

		this->vertical->addWidget(this->widget_array[this->current_widget]);
		this->widget_array[this->current_widget]->show();

		this->buttons[0].setEnabled(true);

		if (this->current_widget == 2 || this->widget_array[this->current_widget + 1] == nullptr) this->buttons[1].setEnabled(false);
		//if (this->current_widget == 2) this->box_for_calculation->show();
	}
}

//void WidgetsControl::previous_method()
//{
//	//qDebug() << this->current_method;
//	if (this->current_method > 0)
//	{
//		this->current_method--;
//		if (this->files_path.find(this->current_method) != this->files_path.end())
//		{
//			this->method_label_box->setText("Method: " + this->method_label[this->current_method]);
//			//qDebug() << this->current_method;
//
//		}
//		else this->previous_method();
//		//else qDebug() << this->current_method;
//
//	}
//}
//
//void WidgetsControl::another_method()
//{
//	//qDebug() << this->current_method;
//	if (this->current_method < 2)
//	{
//		this->current_method++;
//		if (this->files_path.find(this->current_method) != this->files_path.end())
//		{
//			this->method_label_box->setText("Method: " + this->method_label[this->current_method]);
//		}
//		else this->another_method();
//
//	}
//}

WidgetsControl::~WidgetsControl()
{

	delete begin_widget;
	/*delete method_label_box;
	delete[] buttons_box;
	delete horisontal_box;
	delete box_for_calculation;*/
	delete horisontal;
	delete vertical;
}