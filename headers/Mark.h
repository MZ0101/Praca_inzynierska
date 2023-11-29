#pragma once

#include <QImage>
#include <QDir>
#include <QScreen>
#include <QMouseEvent>
#include "Box_for_mark.h"


class Mark : public QWidget
{
    Q_OBJECT

public:
    Mark(QWidget *parent = nullptr);
    ~Mark();
    
    QImage ImagesForMark[2];

    QDir dir;
    QStringList ImageNameList;
    QString PathToTheSourceImagesFolder = "Dane";
 
    int MaxImageNumber{0};
    int WidthScaleForImage{1}, HeightScaleForImage{ 1};
    int ImageWidth, ImageHeight;
    int CurrentLeftImageNumber {0}, CurrentRightImageNumber {0}; 

    QGraphicsScene* TempeorarySceneForImageChange = nullptr;
    QGraphicsPixmapItem* PixmapItemForTemporaryScene = nullptr;
    
   
    Box_for_mark* BoxsForMarkBeginAndEndPoint = nullptr;
    Buttons* ButtonForConfirm = nullptr;
    QHBoxLayout* ButtonsHorisontalLayout = nullptr;

    QHBoxLayout *HorisontalLayoutForBoxsForMark = nullptr;
    QVBoxLayout* MainVerticalLayoutForAllItems = nullptr;

private:

    void LoadImagesNameFromDir();
    void CheckImageSizeAndChangeViewSize();
    void ChangeToThePreviousImage();
    void ChangeToTheNextImage();

    bool eventFilter(QObject* object, QEvent* event) override;
    void RetrievingPixelPositionAndCheckingColor(QMouseEvent* MouseEvent ,int& NumberBoxThatSendSignal);
    void SelectingASelectedPixelAndPoints(QPointF& ClickedPosition , int& NumberBoxThatSendSignal);
       
private slots:
        
        void ImageChangeIfTheImageNumberChanged();
};
