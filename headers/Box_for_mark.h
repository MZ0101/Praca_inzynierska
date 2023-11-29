#pragma once

#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "Label.h"
#include "LineEdit.h"
#include "Buttons.h"
#include "View.h"

class Box_for_mark : public QGroupBox
{
public:
	//Pudelko_wybieranie(QWidget* parent = nullptr);
	Box_for_mark(QWidget *parent = nullptr);
	~Box_for_mark();

	Label *files_name = nullptr;
	//Label *label_image = nullptr;
	View* ViewForImage = nullptr;
	Label *data_labels = nullptr;
	LineEdit *edit = nullptr;
	Buttons *buttons = nullptr;

	QHBoxLayout *h_layouts = nullptr;
	QVBoxLayout *v_layout = nullptr;

};