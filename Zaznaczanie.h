#pragma once

#include <QImage>
#include <QDir>
#include <QScreen>
#include <QMouseEvent>
#include "Pudelko_wybieranie.h"


class Zaznaczanie : public QWidget
{
    Q_OBJECT

public:
    Zaznaczanie(QWidget *parent = nullptr);
    ~Zaznaczanie(); 
    // alokacja statyczna
    QImage image[2];

    QDir dir;
    QStringList files_list;
    QString path = "Dane";
    int size{0};
    int current_l {0}, current_r {0}; 
   

    // alokacja dynamiczna
    Pudelko_wybieranie *boxs = nullptr;
    Buttons* button = nullptr;
    QHBoxLayout* b_horisontal = nullptr;
    
    QHBoxLayout *horisontal = nullptr;
    QVBoxLayout* vertical = nullptr;

protected:
    
    bool eventFilter(QObject* object, QEvent* event) override;

    protected slots:
        void previous_r();
        void another_r();
        void previous_l();
        void another_l();
        void if_z_value_changet();
};
