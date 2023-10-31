#include "Mark.h"

Mark::Mark(QWidget *parent) : QWidget(parent)
{
    this->dir.setPath(this->path);
    this->files_list = this->dir.entryList(QDir::Files | QDir::NoDotAndDotDot);
    this->files_list.erase(this->files_list.begin());
    this->size = this->files_list.size()-1;

    this->path += "//";
    
    QString boxs_namse[2] = { "Begining","End" };

   // void(Mark:: * functions[4]) () = { &Mark::previous_l, &Mark::another_l,&Mark::previous_r, &Mark::another_r};

    this->boxs = new Box_for_mark[2];
    //this->boxs = new Pudelko_wybieranie[2];

    this->horisontal = new QHBoxLayout();

    for (size_t i{ 0 }; i < 2; i++)
    {
        this->boxs[i].setTitle(boxs_namse[i]);
        this->boxs[i].label_image->installEventFilter(this);
        this->boxs[i].label_image->setMouseTracking(true);
        QObject::connect(&this->boxs[i].edit[2], SIGNAL(textChanged(const QString&)), this, SLOT(if_z_value_changed()));

       // QObject::connect(&(this->boxs[0].buttons[i]), &QPushButton::clicked, this, functions[i + 2]);
        //QObject::connect(&(this->boxs[1].buttons[i]), &QPushButton::clicked, this, functions[i+2]);

         QObject::connect(&(this->boxs[i].buttons[0]), &QPushButton::clicked, this, &Mark::previous );
         QObject::connect(&(this->boxs[i].buttons[1]), &QPushButton::clicked, this, &Mark::another);


        this->image[i].load(this->path + this->files_list[0]);
        this->boxs[i].label_image->setPixmap(QPixmap::fromImage(this->image[i]).scaled(QSize(800, 800), Qt::KeepAspectRatio));
        this->boxs[i].files_name->setText(this->files_list[0]);
        
        this->horisontal->addWidget(&this->boxs[i]);
    }

    this->vertical = new QVBoxLayout(this);
    this->button = new Buttons();
    this->b_horisontal = new QHBoxLayout();
    this->b_horisontal->setAlignment(Qt::AlignCenter);
    this->b_horisontal->addWidget(this->button);

    this->button->setText("Confirm");
    this->vertical->addLayout(this->b_horisontal);
    this->vertical->addLayout(this->horisontal);
    
    this->setLayout(this->vertical);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowMaximizeButtonHint);
}

void Mark::previous()
{

    Buttons* box_buttons_clicked = qobject_cast<Buttons *>(sender());

    if (box_buttons_clicked == &this->boxs[0].buttons[0])
    {
        if (this->current_l > 0)
        {
            this->current_l--;

            this->boxs[0].edit[2].setText(QString::number(this->current_l));
        }
    }

    else  
    {
        if (this->current_r > 0)
        {
            this->current_r--;

            this->boxs[1].edit[2].setText(QString::number(this->current_r));
        }
    }


   
}
void Mark::another()
{
    Buttons* box_buttons_clicked = qobject_cast<Buttons*>(sender());
    
    if (box_buttons_clicked == &this->boxs[0].buttons[1])
    {
        if (this->current_l < this->size)
        {
            this->current_l++;
            this->boxs[0].edit[2].setText(QString::number(this->current_l));

        }

    }

    else
    {
        if (this->current_r < this->size)
        {
            this->current_r++;
            this->boxs[1].edit[2].setText(QString::number(this->current_r));

        }

    }

}

//void Mark::previous_r()
//{
//    if (this->current_r > this->current_l)
//    {
//        this->current_r--;
//        this->process(this->current_r, 1);
//        this->boxs[1].edit[2].setText(QString::number(this->current_r));
//    }
//}
//void Mark::another_r()
//{
//    if (this->current_r < this->size)
//    {
//        this->current_r++;
//        this->boxs[1].edit[2].setText(QString::number(this->current_r));
//        this->process(this->current_r,1);
//    }
//}



bool Mark::eventFilter(QObject* object, QEvent* event)
{
    if ((this->boxs[0].label_image == object || this->boxs[1].label_image == object) && event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);
        int box_number{0};
        int x = mouse_event->x();
        int y = mouse_event->y();
        for (size_t i{ 0 }; i < 2; i++)
        {
            if (this->boxs[i].label_image == object)
            {
                box_number = i;
            }
        }
        QImage image = this->boxs[box_number].label_image->pixmap().toImage();

        QColor current_p = image.pixelColor(x, y);

        if (current_p.red() == 255 && current_p.blue() == 255 && current_p.green() == 255)
        {
            int x_original = static_cast<int>(static_cast<double>(x*200 / 800));
            int y_original = static_cast<int>(static_cast<double>(y*200 / 800 ));
           
            image = this->image[box_number].copy();
            this->boxs[box_number].edit[0].setText(QString::number(x_original));
            this->boxs[box_number].edit[1].setText(QString::number(y_original));

            //Czerwony
            image.setColor(2, qRgb(255, 0, 0));

            image.setPixel(x_original,y_original, 2);
            this->boxs[box_number].label_image->setPixmap(QPixmap());
            
            this->boxs[box_number].label_image->setPixmap(QPixmap::fromImage(image).scaled(QSize(800,800), Qt::KeepAspectRatio));
        }
    }
    return QWidget::eventFilter(object, event);
}

void Mark::if_z_value_changed()
{
    QObject *obiect_send = sender();
    int z_value{ 0 };
    uint number{ 0 };

    if (&this->boxs[0].edit[2] == obiect_send)
    {
        z_value = this->boxs[0].edit[2].text().toUInt();
       // if (z_value > this->boxs[1].edit[2].text().toUInt()) return;
           
    }
    else
    {
        z_value = this->boxs[1].edit[2].text().toUInt();
        number = 1;
    }

    if (z_value <= this->size && z_value > 0)
    {
        //(number == 0) ? this->current_l = z_value : this->current_r = z_value;

        if (number == 0)  this->current_l = z_value;
        else this->current_r = z_value;
       
        this->image[number].load(this->path + this->files_list[z_value]);
        this->boxs[number].files_name->setText(this->files_list[z_value]);

        for (uint i{ 0 }; i < 2; i++)
        {
            this->boxs[number].edit[i].setText("");
        }


        this->boxs[number].label_image->setPixmap(QPixmap::fromImage(this->image[number]).scaled(QSize(800, 800), Qt::KeepAspectRatio));
        
    }
    
}

Mark::~Mark()
{
    delete [] boxs;
    delete  horisontal;
    delete button;
    delete b_horisontal;
    delete vertical;
}