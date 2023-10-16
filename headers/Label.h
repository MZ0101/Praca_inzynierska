#pragma once
#include <QLabel>


class Label : public QLabel
{
public:

    Label(QWidget* parent = nullptr);
    ~Label();
 

    void style_view(QString name = "default");


};