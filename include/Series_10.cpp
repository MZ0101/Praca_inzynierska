#include "Series_10.h"
Series_10::Series_10(QWidget* parent) : QWidget(parent)
{
    this->boxs_data = new Box_for_10_series[10];
    this->horisontal_for_boxs = new QHBoxLayout();
    this->horisontal_for_boxs->setAlignment(Qt::AlignCenter);
    //this->vertical_main = new QVBoxLayout();

    this->verticals = new QVBoxLayout[2];
    this->button_for_calculate = new Buttons();

    this->button_for_calculate->setText("Calculate");
    this->button_for_calculate->setFixedWidth(200);
    this->button_for_calculate->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    this->button_for_randomize = new Buttons();

    QObject::connect(this->button_for_randomize, &QPushButton::clicked,this, &Series_10::randomization_of_points);

    this->button_for_randomize->setText("Randomize points");
    this->button_for_randomize->setFixedWidth(200);


    this->horisontal_for_bottom_buttons = new QHBoxLayout();

    this->horisontal_for_bottom_buttons->addWidget(this->button_for_randomize);
    this->horisontal_for_bottom_buttons->addWidget(this->button_for_calculate);
    


    for (size_t i{ 0 }; i < 10; i++)
    {
        if (i < 5)
        {
            this->verticals[0].addWidget(&this->boxs_data[i]);
        }
        else
        {
            this->verticals[1].addWidget(&this->boxs_data[i]);
        }

        QObject::connect(this->boxs_data[i].button, &QPushButton::clicked, [this, i]() {Series_10::mark_button(this->boxs_data[i].button); });

    }

    this->horisontal_for_boxs->addLayout(&this->verticals[0]);
    this->horisontal_for_boxs->addLayout(&this->verticals[1]);

    this->vertical_main.addLayout(this->horisontal_for_boxs);
    this->vertical_main.addLayout(this->horisontal_for_bottom_buttons);
    this->vertical_main.setAlignment(this->button_for_calculate, Qt::AlignHCenter);

  
    this->setLayout(&this->vertical_main);
}

void Series_10::mark_button(Buttons* button_clicked)
{
    this->hide();
    for (size_t i{ 0 }; i < 10; i++)
    {
        if (button_clicked == this->boxs_data[i].button)
        {
            this->button_number = i;
            break;
        }
    }
}

void Series_10::randomization_of_points()
{

    QDir dir("Dane");
    QStringList files_list = dir.entryList(QDir::Files | QDir::NoDotAndDotDot);

    int SizeImagesList = files_list.size();

    QImage ImageForRandomize("Dane//" + files_list[0]);

    int ImageWidth = ImageForRandomize.width();
    int ImageHeight = ImageForRandomize.height();
    
   
   
    int begin[3] = { 0,0,0 };
    int end[3] = { 0,0,0 };
    
 
        for (int i{ 0 }; i < 10; i++)
        {
            QRgb pixel_color;
            int ImageNumberDifference{ 0 };

            while (ImageNumberDifference < 10)
            {
                do
                {
                    begin[0] = std::rand() % ImageWidth;
                    begin[1] = std::rand() % ImageHeight;
                    begin[2] = std::rand() % SizeImagesList;

                    ImageForRandomize.load("Dane//" + files_list[begin[2]]);
                    pixel_color = ImageForRandomize.color(ImageForRandomize.pixelIndex(begin[0], begin[1]));

                } while (qRed(pixel_color) != 255 && qBlue(pixel_color) != 255 && qGreen(pixel_color) != 255);

                do
                {
                    end[0] = std::rand() % ImageWidth;
                    end[1] = std::rand() % ImageHeight;
                    end[2] = std::rand() % SizeImagesList;

                    ImageForRandomize.load("Dane//" + files_list[end[2]]);
                    pixel_color = ImageForRandomize.color(ImageForRandomize.pixelIndex(end[0], end[1]));

                } while (qRed(pixel_color) != 255 && qBlue(pixel_color) != 255 && qGreen(pixel_color) != 255);

                ImageNumberDifference = std::abs(begin[2] - end[2]);
            }
            
            for (size_t b{ 0 }; b < 3; b++)
            {
                this->boxs_data[i].begin_labels[b].setText(QString::number(begin[b]));
                this->boxs_data[i].end_labels[b].setText(QString::number(end[b]));
            }

        }
}

Series_10::~Series_10()
{
	delete[] boxs_data;
	delete button_for_calculate;
    delete button_for_randomize;
	delete[] verticals;
    delete horisontal_for_boxs;
    delete horisontal_for_bottom_buttons;
}