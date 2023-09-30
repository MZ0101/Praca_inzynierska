#pragma once
#include <QWidget>
#include <QLineEdit>

class LineEdit :public QLineEdit
{
public:
	LineEdit(QWidget* parent = nullptr);
	~LineEdit();

};

