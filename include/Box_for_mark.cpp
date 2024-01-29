#include "Box_for_mark.h"

Box_for_mark::Box_for_mark(QWidget* parent) : QGroupBox(parent)
{
	
	this->setAlignment(Qt::AlignHCenter);

	this->files_name = new Label();
	this->ViewForImage = new View();
	this->data_labels = new Label[3];
	this->edit = new LineEdit[3];
	this->buttons = new Buttons[2];

	this->files_name->setStyleSheet("background-color: white; border : 2px solid black; font-weight: bold;");
	this->files_name->setFont(QFont("Arial", 11));
	this->files_name->setFixedSize(225, 25);

	QString button_names[2] = { "Previosus","Another" };
	QString data_labels_text[3] = { "x (max: 200):", "y (max: 200) :" , "z (max: 207):" };

	this->h_layouts = new QHBoxLayout[2];
	this->v_layout = new QVBoxLayout();
	this->v_layout->setAlignment(Qt::AlignCenter);

	for (size_t i{ 0 }; i < 3; i++)
	{
		if (i < 2)
		{
			this->h_layouts[i].setAlignment(Qt::AlignHCenter);
			this->buttons[i].setText(button_names[i]);

			this->h_layouts[1].addWidget(&this->buttons[i]);
			this->v_layout->addLayout(&this->h_layouts[i]);

			if (i == 0)
			{
				this->h_layouts[1].addWidget(this->files_name);
			}
				
		}
		    this->data_labels[i].setText(data_labels_text[i]);
			this->data_labels[i].setFixedSize(QSize(80,25));
			this->h_layouts[0].addWidget(&this->data_labels[i]);
			this->h_layouts[0].addWidget(&this->edit[i]);
			this->edit[i].setText("0");
	}
	this->v_layout->addWidget(this->ViewForImage);
	this->setLayout(this->v_layout);

	this->setAlignment(Qt::AlignCenter);
}

Box_for_mark::~Box_for_mark()
{
	delete files_name;
	delete ViewForImage;
	delete [] data_labels;
	delete [] edit;
	delete [] buttons;
	delete [] h_layouts;
	delete v_layout;
}