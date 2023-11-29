#pragma once

#include "Series_1.h"
#include "Series_10.h"
#include "Result_10.h"
#include "Mark.h"
#include "SearchAlgorithm.h"
#include "Control_Widget.h"

#include <QScreen>
#include <QMessageBox>
#include <QMainWindow>
#include <QApplication>

class Main_class : public QObject
{
    Q_OBJECT

public:
    Main_class(QObject* parent = nullptr);
    ~Main_class();

    WidgetsControl* control_widget = nullptr;

    Series_1* series_1 = nullptr;
    Series_10* series_10 = nullptr;
    Mark* MarkingPoints = nullptr;

    Result_1* result_1 = nullptr;
    Result_10* result_10 = nullptr;
    Begin_Widget* widget = nullptr;
    QVBoxLayout* vertical = nullptr;

    int StartingPoint[3] = { 0,0,0 };
    int EndPoint[3] = { 0,0,0 };

    float AverageRoadCost{ 0.0 };

    QString result_path;


    void ChangingTheSizeAndPositionOfTheMainWidget(QWidget* widget);

    void SelectedRouteCalculationOption();
    void CalculatingTheCostOfTheRoad();
    
    void AcceptanceOfMarkedPoints();
    void CreatingAWidgetToDisplay_RESULT_For_ONE_Series();
    void CreatingAWidgetToDisplay_RESULTS_sFor_TEN_Series();
    void ONE_DataSeriesCreatingAWidgetToSelect();
    void TEN_DataSeriesCreatingAWidgetToSelect();

    double EucleideanDistanceCalculation();
};