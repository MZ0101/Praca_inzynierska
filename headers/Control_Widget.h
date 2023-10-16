#pragma once

#include "Buttons.h"
#include "Label.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QGroupBox>

//#include <map>

class Begin_Widget :public QWidget
{
	Q_OBJECT
public:
	Begin_Widget(QWidget* parent = nullptr);
	~Begin_Widget() {};

	QVBoxLayout main_layout;


	QHBoxLayout horisontal_box_1;
	QHBoxLayout horisontal_box_2;

	QVBoxLayout vertical_1[2];
	
	QCheckBox check_1[2];
	QCheckBox check_2[3];
	Buttons button_1;
	
protected:
	void currentCheckBox_1();
	void currentCheckBox_2();

};


class WidgetsControl : public QWidget
{
	Q_OBJECT

public:
	WidgetsControl();
	~WidgetsControl();

	QHBoxLayout* horisontal = nullptr;
	QVBoxLayout* vertical = nullptr;

	Begin_Widget* begin_widget = nullptr;

	Buttons buttons[2];
	QWidget* widget_array[3] = { nullptr,nullptr, nullptr };

	int current_widget{ 0 };

	//QGroupBox* box_for_calculation = nullptr;
	//QHBoxLayout* horisontal_box = nullptr;
	//Buttons *buttons_box = nullptr;
	//Label *method_label_box = nullptr;
	//std::map<int, QString> method_label =  { {0,"Dajkstra"}, {1,"Total A*"}, {2, "Euklides A*"}};
	//std::map<int, QString> files_path = {};
	//int current_method{ 0 };

	

	/*void previous_method();
	void another_method();*/

protected:

	void previous_widget();
	void another_widget();


};