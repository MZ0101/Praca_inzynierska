#pragma once

#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "Label.h"
#include "LineEdit.h"
#include "Buttons.h"

class Pudelko_wybieranie : public QGroupBox
{
public:
	//Pudelko_wybieranie(QWidget* parent = nullptr);
	Pudelko_wybieranie(QWidget *parent = nullptr);
	~Pudelko_wybieranie();

	Label *files_name = nullptr;
	Label *label_image = nullptr;
	Label *data_labels = nullptr;
	LineEdit *edit = nullptr;
	Buttons *buttons = nullptr;

	QHBoxLayout *h_layouts = nullptr;
	QVBoxLayout *v_layout = nullptr;

protected:
	//void mousePressEvent(QMouseEvent* event) override;

};

