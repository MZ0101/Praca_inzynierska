#pragma once
#include <qgroupbox.h>

#include "Label.h"
#include "LineEdit.h"
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QVBoxLayout>

class Pudelko : public QGroupBox
{
	
public:
	Pudelko(QWidget* parent = nullptr, QString title = "default");
	~Pudelko();

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