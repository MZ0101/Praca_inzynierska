#pragma once

#include "Label.h"
#include "LineEdit.h"
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QGroupBox>

class Box_for_1_series : public QGroupBox
{
	
public:
	Box_for_1_series(QWidget* parent = nullptr, QString title = "default");
	~Box_for_1_series();

	Label* label = nullptr;
	LineEdit* edit = nullptr;
	QHBoxLayout* group = nullptr;
	QVBoxLayout* main_group = nullptr;

	int currentLineEdit{ 0 };

protected:

	void mousePressEvent(QMouseEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;
	void UpFocus();
	void DownFocus();

};