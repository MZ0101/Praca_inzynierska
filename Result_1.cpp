#include "Result_1.h"

Result_1::Result_1(QWidget* parent , QString path) : QWidget(parent)
{
    this->files_path = path;

    this->setFocus();
    this->setFocusPolicy(Qt::StrongFocus);

    this->hlayout.addWidget(&this->result);
    this->hlayout.setAlignment(&this->result, Qt::AlignHCenter);

    this->result.setFixedSize(200,25);
    this->result.setFont(QFont("Arial", 11));

    this->image_name.setFixedSize(225, 25);
    this->image_name.setFont(QFont("Arial", 11));
    this->image_name.setStyleSheet("background-color: white; border: 1px solid black; font-weight: bold;");


    this->main_hlayout.setAlignment(Qt::AlignHCenter);

   
    QStringList names = { "Beginning","Previous","Another","End" };
    void (Result_1:: * functions[4])() = { &Result_1::begin,&Result_1::previous,&Result_1::another, &Result_1::end };


    for (size_t i{ 0 }; i < 4; i++)
    {
        this->buttons[i].setText(names[i]);
        this->main_hlayout.addWidget(&this->buttons[i]);
        if (i == 1)
        {

            this->main_hlayout.addWidget(&this->image_name);
            
        }
            
        QObject::connect(&this->buttons[i], &QPushButton::clicked, this, functions[i]);
    }

    this->main_layout.addLayout(&this->hlayout);
    this->main_layout.addLayout(&this->main_hlayout);
    this->main_layout.addWidget(&this->image_view);
    this->setLayout(&this->main_layout);
}

bool Result_1::event(QEvent* event) 
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent* key_event = static_cast<QKeyEvent*>(event);
        if (key_event->key() == Qt::Key_Left)
        {
            this->previous();
        }
        else if (key_event->key() == Qt::Key_Right)
        {
            this->another();
        }
    }
    else if (event->type() == QEvent::Wheel)
    {

        this->image_view.wheelEvent(static_cast<QWheelEvent*>(event));

    }
    return QWidget::event(event);
}

void Result_1::end()
{
    if (this->files_list.size() > 0)
    {
        this->current_image_index = this->max_image_index;
        processing();
    }
}
void Result_1::previous()
{
    if (this->current_image_index > 0)
    {
        this->current_image_index--;
        processing();
    }
}
void Result_1::another()
{
    if (this->current_image_index < this->max_image_index)
    {
        this->current_image_index++;
        processing();
    }
}
void Result_1::begin()
{
    if (this->files_list.size() > 0)
    {
        this->current_image_index = 0;
        processing();
    }
}

inline void Result_1::processing()
{
    this->scene = this->image_view.scene();
    this->pixmapItem = dynamic_cast<QGraphicsPixmapItem*>(scene->items().first());

    this->image_name.setText("Image name: "+this->files_list[this->current_image_index]);

    this->image.load(this->files_path + this->files_list[this->current_image_index]);
    this->scene->setSceneRect(0, 0, 800, 800);
    this->image = this->image.scaled(QSize(800, 800), Qt::KeepAspectRatio);
    this->pixmapItem->setPixmap(QPixmap::fromImage(this->image.scaled(800, 800)));
}

void Result_1::if_empty()
{
    this->scene = this->image_view.scene();
    this->pixmapItem = dynamic_cast<QGraphicsPixmapItem*>(scene->items().first());

    this->image_name.setText("Image name: Empty");
    this->image_name.setStyleSheet("background-color: white; border : 2px solid red;");

    this->image.load("empty.jpg");
   // this->image = this->image.scaled(QSize(800, 800), Qt::KeepAspectRatio);

    //this->scene->setSceneRect(0, 0, 800, 800);
    this->image = this->image.scaled(QSize(800, 800), Qt::KeepAspectRatio);
    this->pixmapItem->setPixmap(QPixmap::fromImage(this->image.scaled(800, 800)));
}

void Result_1::image_reamove()
{
#include <QFile>

    QString files_path{};
    //QString path{};
    QDir dir{};
    QStringList files_list = {};

   
        files_path = this->files_path;
        files_path = files_path ;
        dir.setPath(files_path);
        files_path += "//";

       /* files_list.clear();*/
        files_list = dir.entryList(QDir::Files);

        for (const QString& file_name : files_list)
        {
            QFile file(dir.filePath(file_name));

            file.remove();

        
    }
}

void Result_1::image_reload()
{

    this->dir.setPath(this->files_path);
    this->files_path += "//";

    this->files_list = this->dir.entryList(QDir::Files);
    this->max_image_index = this->files_list.size() - 1;

    if (this->files_list.size())
    {
        this->image.load(this->files_path + this->files_list[this->current_image_index]);
        this->image = this->image.scaled(QSize(800, 800), Qt::KeepAspectRatio);

        this->image_view.scene_v.addPixmap(QPixmap::fromImage(this->image).scaled(800, 800));
        this->image_name.setText("Image name : " + this->files_list[this->current_image_index]);


        this->result.setStyleSheet("background-color: white; border: 2px solid green; font-weight: bold;");
       
    }
    else
    {
        this->image.load("Result_1//empty.jpg");
        this->image = this->image.scaled(QSize(800, 800), Qt::KeepAspectRatio);
        this->image_view.scene_v.addPixmap(QPixmap::fromImage(this->image).scaled(800, 800));
        this->image_name.setText("Image name: Empty");

        this->result.setStyleSheet("background-color: white; border: 2px solid red; font-weight: bold;");
    }
}
