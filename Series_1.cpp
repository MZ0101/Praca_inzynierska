#include "Series_1.h"

Series_1::Series_1(QWidget *parent) : QWidget(parent)
{
	this->main_layout = new QVBoxLayout();

	this->buttons[0].setText("Mark");
	this->buttons[1].setText("Calculate");

	for (size_t i{ 0 }; i < 2; i++)
	{
		this->button_group.addWidget(&this->buttons[i]);
		this->buttons[i].setFixedSize(QSize(120, 30));
	}
	this->right_box.setTitle("Start data");
	this->left_box.setTitle("Target data");
	this->box_group.addWidget(&this->right_box);
	this->box_group.addWidget(&this->left_box);

	this->main_layout->addLayout(&this->box_group);
	this->main_layout->addLayout(&this->button_group);
	this->setLayout(this->main_layout);

	this->removed_files();	
}
void Series_1::removed_files()
{
	QDir dir{};
	QStringList files_list = {};
	dir.setPath(this->path);
	this->path += "//";

	files_list = dir.entryList(QDir::Files);

	for (const QString& file_name : files_list)
	{
		QFile file(dir.filePath(file_name));

		file.remove(file_name);
	}
}