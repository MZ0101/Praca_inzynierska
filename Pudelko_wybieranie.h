#pragma once

#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "E://Inzynierka_2//Label.h"
#include "E://Inzynierka_2//LineEdit.h"
#include "E://Inzynierka_2//Buttons.h"

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

