#include "Mark.h"

Mark::Mark(QWidget *parent) : QWidget(parent)
{

    QString BoxsForMarkBeginAndEndPoint_Name[2] = { "Begining Data","End Data" };

    this->BoxsForMarkBeginAndEndPoint = new Box_for_mark[2];
    this->HorisontalLayoutForBoxsForMark = new QHBoxLayout();
    this->MainVerticalLayoutForAllItems = new QVBoxLayout();
    this->ButtonForConfirm = new Buttons();
    this->ButtonsHorisontalLayout = new QHBoxLayout();

    this->LoadImagesNameFromDir();

    this->CheckImageSizeAndChangeViewSize();

    for (size_t i{ 0 }; i < 2; i++)
    {
        this->BoxsForMarkBeginAndEndPoint[i].setTitle(BoxsForMarkBeginAndEndPoint_Name[i]);
        this->BoxsForMarkBeginAndEndPoint[i].ViewForImage->installEventFilter(this);
       
        QObject::connect(&(this->BoxsForMarkBeginAndEndPoint[i].buttons[0]), &QPushButton::clicked, this, &Mark::ChangeToThePreviousImage);
        QObject::connect(&(this->BoxsForMarkBeginAndEndPoint[i].buttons[1]), &QPushButton::clicked, this, &Mark::ChangeToTheNextImage);

        QObject::connect(&this->BoxsForMarkBeginAndEndPoint[i].edit[2], SIGNAL(textChanged(const QString&)), this, SLOT(ImageChangeIfTheImageNumberChanged()));

        this->BoxsForMarkBeginAndEndPoint[i].files_name->setText(this->ImageNameList[0]);
       
        this->HorisontalLayoutForBoxsForMark->addWidget(&this->BoxsForMarkBeginAndEndPoint[i]);
    }

    this->ButtonsHorisontalLayout->setAlignment(Qt::AlignCenter);
    this->ButtonsHorisontalLayout->addWidget(this->ButtonForConfirm);

    this->ButtonForConfirm->setText("Confirm");
    this->MainVerticalLayoutForAllItems->addLayout(this->ButtonsHorisontalLayout);
    this->MainVerticalLayoutForAllItems->addLayout(this->HorisontalLayoutForBoxsForMark);
    
    this->setLayout(this->MainVerticalLayoutForAllItems);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowMaximizeButtonHint);
}

void Mark::LoadImagesNameFromDir()
{
    
    this->dir.setPath(this->PathToTheSourceImagesFolder);
    this->ImageNameList = this->dir.entryList(QDir::Files | QDir::NoDotAndDotDot);
    this->MaxImageNumber = this->ImageNameList.size() - 1;

    this->PathToTheSourceImagesFolder += "//";
}

void Mark::CheckImageSizeAndChangeViewSize()
{
    QImage ImageForChangeViewSize(this->PathToTheSourceImagesFolder + this->ImageNameList[0]);

    this->WidthScaleForImage = this->BoxsForMarkBeginAndEndPoint[0].ViewForImage->width() / ImageForChangeViewSize.width();
    this->HeightScaleForImage = this->BoxsForMarkBeginAndEndPoint[0].ViewForImage->height() / ImageForChangeViewSize.height();

    if (this->WidthScaleForImage <= 1 || this->HeightScaleForImage <= 1)
    {
        this->WidthScaleForImage = 1;
        this->HeightScaleForImage = 1;
    }

    this->ImageWidth = ImageForChangeViewSize.width() * this->WidthScaleForImage;
    this->ImageHeight = ImageForChangeViewSize.height() * this->WidthScaleForImage;

    QPixmap PixMapForSceneOnViews = QPixmap::fromImage(ImageForChangeViewSize.scaled(this->ImageWidth, this->ImageHeight));

    for (int i{ 0 }; i < 2; i++)
    {

        QGraphicsPixmapItem* PixMapForSceneOnViewsItem = this->BoxsForMarkBeginAndEndPoint[i].ViewForImage->scene()->addPixmap(PixMapForSceneOnViews);
        this->ImagesForMark[i].load(this->PathToTheSourceImagesFolder + this->ImageNameList[0]);

        this->BoxsForMarkBeginAndEndPoint[i].ViewForImage->setFixedSize(this->ImageWidth, this->ImageHeight);
        this->BoxsForMarkBeginAndEndPoint[i].ViewForImage->scene_v.setSceneRect(0, 0, this->ImageWidth, this->ImageHeight);

    }
}

void Mark::ChangeToThePreviousImage()
{

    Buttons* box_buttons_clicked = qobject_cast<Buttons *>(sender());

    if (box_buttons_clicked == &this->BoxsForMarkBeginAndEndPoint[0].buttons[0])
    {
        if (this->CurrentLeftImageNumber > 0)
        {
            this->CurrentLeftImageNumber--;

            this->BoxsForMarkBeginAndEndPoint[0].edit[2].setText(QString::number(this->CurrentLeftImageNumber));
        }
    }

    else  
    {
        if (this->CurrentRightImageNumber > 0)
        {
            this->CurrentRightImageNumber--;

            this->BoxsForMarkBeginAndEndPoint[1].edit[2].setText(QString::number(this->CurrentRightImageNumber));
        }
    }
}

void Mark::ChangeToTheNextImage()
{
    Buttons* BoxButtonsClicked = qobject_cast<Buttons*>(sender());
    
    if (BoxButtonsClicked == &this->BoxsForMarkBeginAndEndPoint[0].buttons[1])
    {
        if (this->CurrentLeftImageNumber < this->MaxImageNumber)
        {
            this->CurrentLeftImageNumber++;
            this->BoxsForMarkBeginAndEndPoint[0].edit[2].setText(QString::number(this->CurrentLeftImageNumber));
        }
    }

    else
    {
        if (this->CurrentRightImageNumber < this->MaxImageNumber)
        {
            this->CurrentRightImageNumber++;
            this->BoxsForMarkBeginAndEndPoint[1].edit[2].setText(QString::number(this->CurrentRightImageNumber));

        }
    }

}

void Mark::ImageChangeIfTheImageNumberChanged()
{
    QObject* ObjectThatSendTheSignal = sender();

    int NumberBoxThatSendSignal = &this->BoxsForMarkBeginAndEndPoint[0].edit[2] == ObjectThatSendTheSignal ? 0 : 1;

    int ImageNumber = NumberBoxThatSendSignal == 0 ? this->BoxsForMarkBeginAndEndPoint[0].edit[2].text().toUInt() : this->BoxsForMarkBeginAndEndPoint[1].edit[2].text().toUInt();

    if (ImageNumber <= this->MaxImageNumber && ImageNumber > 0)
    {

        if (NumberBoxThatSendSignal == 0)
        {
            this->CurrentLeftImageNumber = ImageNumber;
        }

        else
        {
            this->CurrentRightImageNumber = ImageNumber;
        }

        this->ImagesForMark[NumberBoxThatSendSignal].load(this->PathToTheSourceImagesFolder + this->ImageNameList[ImageNumber]);
        this->BoxsForMarkBeginAndEndPoint[NumberBoxThatSendSignal].files_name->setText(this->ImageNameList[ImageNumber]);

        for (uint i{ 0 }; i < 2; i++)
        {
            this->BoxsForMarkBeginAndEndPoint[NumberBoxThatSendSignal].edit[i].setText("");
        }

        this->TempeorarySceneForImageChange = this->BoxsForMarkBeginAndEndPoint[NumberBoxThatSendSignal].ViewForImage->scene();
        this->PixmapItemForTemporaryScene = dynamic_cast<QGraphicsPixmapItem*>(TempeorarySceneForImageChange->items().first());

        this->PixmapItemForTemporaryScene->setPixmap(QPixmap::fromImage(this->ImagesForMark[NumberBoxThatSendSignal].scaled(QSize(this->ImageWidth, this->ImageHeight))));
    }

}

bool Mark::eventFilter(QObject* object, QEvent* event)
{
    if ((this->BoxsForMarkBeginAndEndPoint[0].ViewForImage == object || this->BoxsForMarkBeginAndEndPoint[1].ViewForImage == object) && event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent* MouseEvent = static_cast<QMouseEvent*>(event);

        int NumberBoxThatSendSignal = (this->BoxsForMarkBeginAndEndPoint[0].ViewForImage == object) ? 0 : 1;

        if (MouseEvent->button() == Qt::LeftButton)
        {

            RetrievingPixelPositionAndCheckingColor(MouseEvent, NumberBoxThatSendSignal);
            
        }

    }

    return QWidget::eventFilter(object, event);
}

void Mark::RetrievingPixelPositionAndCheckingColor(QMouseEvent* MouseEvent, int& NumberBoxThatSendSignal)
{

    QPointF ClickedPosition = this->BoxsForMarkBeginAndEndPoint[NumberBoxThatSendSignal].ViewForImage->mapToScene(MouseEvent->pos());

    this->TempeorarySceneForImageChange = this->BoxsForMarkBeginAndEndPoint[NumberBoxThatSendSignal].ViewForImage->scene();
    this->PixmapItemForTemporaryScene = dynamic_cast<QGraphicsPixmapItem*>(this->TempeorarySceneForImageChange->items().first());

    QImage ImageToSelectThePixel = this->PixmapItemForTemporaryScene->pixmap().toImage();
    QColor CurrentPixel = ImageToSelectThePixel.pixelColor(ClickedPosition.x(), ClickedPosition.y());

    if (CurrentPixel.red() == 255 && CurrentPixel.blue() == 255 && CurrentPixel.green() == 255)
    {
        SelectingASelectedPixelAndPoints(ClickedPosition, NumberBoxThatSendSignal);
    }
 
}

void Mark::SelectingASelectedPixelAndPoints(QPointF& ClickedPosition, int& NumberBoxThatSendSignal)
{
    
    int x_original = ClickedPosition.x() / this->WidthScaleForImage;
    int y_original = ClickedPosition.y() / this->HeightScaleForImage;

    QImage ImageToSelectThePixel = this->ImagesForMark[NumberBoxThatSendSignal].copy();
    this->BoxsForMarkBeginAndEndPoint[NumberBoxThatSendSignal].edit[0].setText(QString::number(x_original));
    this->BoxsForMarkBeginAndEndPoint[NumberBoxThatSendSignal].edit[1].setText(QString::number(y_original));


    ////Czerwony
    ImageToSelectThePixel.setColor(6, qRgb(255, 0, 0));
    ImageToSelectThePixel.setPixel(x_original, y_original, 6);


    this->PixmapItemForTemporaryScene->setPixmap(QPixmap::fromImage(ImageToSelectThePixel.scaled(QSize(this->ImageWidth, this->ImageHeight), Qt::KeepAspectRatio)));
}

Mark::~Mark()
{
    delete [] BoxsForMarkBeginAndEndPoint;
    delete  HorisontalLayoutForBoxsForMark;
    delete ButtonForConfirm;
    delete ButtonsHorisontalLayout;
    delete MainVerticalLayoutForAllItems;
}