#include "Result_10.h"

Result_10::Result_10(QWidget* parent) : QWidget(parent)
{
	this->main_layout = new QHBoxLayout();
	this->buttons = new Buttons[2];

	this->vertical.addLayout(&this->buttons_layout);
	QString buttons_text[2] = { "Previous","Another" };

	for (size_t i{ 0 }; i < 2; i++)
	{
		this->buttons[i].setText(buttons_text[i]);
		this->buttons_layout.addWidget(&this->buttons[i]);
		
	}
	QObject::connect(&this->buttons[0], &QPushButton::clicked, this, &Result_10::previous);
	QObject::connect(&this->buttons[1], &QPushButton::clicked, this, &Result_10::andother);

	this->series_labels = new Label[12];
	this->vertical.addWidget(&this->series_labels[11]);

	this->series_labels[11].setText("Resulsts");
	this->box_on_result.setAlignment(Qt::AlignHCenter);

	for (size_t i{ 0 }; i < 11; i++)
	{
		this->vertical.addWidget(&this->series_labels[i]);
		//this->series_labels[i].setText("Series " + QString::number(i)+": ");
	}
	
	this->main_result = new Result_1(this, this->files_path + "0");
	this->main_result->image_reload();
	this->main_result->main_layout.removeItem(&this->main_result->hlayout);
	this->main_result->result.hide();

	this->box_on_result.setLayout(&this->vertical);
	this->main_layout->addWidget(&this->box_on_result);
	this->main_layout->addWidget(this->main_result);
	this->setLayout(this->main_layout);

}
void Result_10::previous()
{
	if (this->current_series > 0)
	{
		this->series_labels[this->current_series].setStyleSheet("background-color: white; border : 2px solid grey;");
		this->current_series--;
		this->zmiana();	
	}
}
void Result_10::andother()
{
	if (this->current_series < this->max_series)
	{
		this->series_labels[this->current_series].setStyleSheet("background-color: white; border : 2px solid grey;");
		this->current_series++;

		this->zmiana();
	}
}
inline void Result_10::zmiana()
{
	this->main_result->current_image_index = 0;
	//this->main_result->files_path = this->files_path + QString::number(this->series_array[this->current_series]);
	this->main_result->files_path = this->files_path + QString::number(this->current_series);
	this->main_result->dir.setPath(this->main_result->files_path);
	this->main_result->image_name.setFixedWidth(400);
	this->main_result->files_path += "//";

	this->main_result->files_list.clear();
	this->main_result->files_list = this->main_result->dir.entryList(QDir::Files);

	if (this->main_result->files_list.size() > 0)
	{
		this->main_result->max_image_index = this->main_result->files_list.size() - 1;
		this->main_result->processing();
		this->main_result->image_name.setText("Image name: " + this->main_result->files_list[this->main_result->current_image_index]);
	}
	this->series_labels[this->current_series].setStyleSheet("background-color: white; border : 2px solid green; font-weight: bold;");


	for (int i{ this->max_series + 1 }; i < 9; i++)
	{

		this->series_labels[i].setText("EMPTY");
		this->series_labels[i].setStyleSheet("background-color: white; border : 2px solid red;");
	}

}

void Result_10::image_remove()
{
#include <QFile>

	QString files_path{};
	QString path{};
	QDir dir{};
	QStringList files_list = {};

	for (size_t i{ 0 }; i < 10; i++)
	{
		files_path = this->files_path;
		path = files_path + QString::number(i);
		dir.setPath(path);
		path += "//";

		files_list.clear();
		files_list = dir.entryList(QDir::Files);

		for (const QString& file_name : files_list)
		{
			QFile file(dir.filePath(file_name));

			file.remove();

		}
	}
}

Result_10::~Result_10()
{
	if (buttons != nullptr)delete[] buttons;
	if (series_labels != nullptr) delete[] series_labels;
	delete main_result;
	delete main_layout;
}