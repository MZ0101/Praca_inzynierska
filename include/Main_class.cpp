#include "Main_class.h"

Main_class::Main_class(QObject* parent) : QObject(parent)
{
    this->control_widget = new WidgetsControl();
 
    QObject::connect(&this->control_widget->buttons[0], &QPushButton::clicked, [&]() {

        this->ChangingTheSizeAndPositionOfTheMainWidget(this->control_widget);

        });

    QObject::connect(&this->control_widget->buttons[1], &QPushButton::clicked, [&]() {

        this->ChangingTheSizeAndPositionOfTheMainWidget(this->control_widget);

        });

    QObject::connect(&this->control_widget->begin_widget->button_1, &QPushButton::clicked, this, &Main_class::SelectedRouteCalculationOption);
   

    this->ChangingTheSizeAndPositionOfTheMainWidget(this->control_widget);
    this->control_widget->show();

}

void Main_class::ChangingTheSizeAndPositionOfTheMainWidget(QWidget* widget)
{
    widget->adjustSize();
    QScreen* primaryScreen = QGuiApplication::primaryScreen();

    QRect ChangingTheSizeAndPositionOfTheMainWidgetRect = primaryScreen->geometry();

    int ChangingTheSizeAndPositionOfTheMainWidgetWidth = ChangingTheSizeAndPositionOfTheMainWidgetRect.width();
    int ChangingTheSizeAndPositionOfTheMainWidgetHeight = ChangingTheSizeAndPositionOfTheMainWidgetRect.height();
    
    widget->move((ChangingTheSizeAndPositionOfTheMainWidgetWidth - widget->width()) / 2, (ChangingTheSizeAndPositionOfTheMainWidgetHeight - widget->height()) / 2);
}

void Main_class::SelectedRouteCalculationOption()
{
 
    if (!this->MarkingPoints)
    {
        this->MarkingPoints = new Mark();
        QObject::connect(this->MarkingPoints->ButtonForConfirm, &QPushButton::clicked, this, &Main_class::AcceptanceOfMarkedPoints);
        this->ChangingTheSizeAndPositionOfTheMainWidget(this->MarkingPoints);
    }

    if (this->control_widget->begin_widget->check_1[0].isChecked())
    {
        this->ONE_DataSeriesCreatingAWidgetToSelect();
    }
    else 
    {
        this->TEN_DataSeriesCreatingAWidgetToSelect();
    }

    this->control_widget->begin_widget->hide();
    this->control_widget->current_widget++;
    this->control_widget->vertical->removeWidget(this->control_widget->widget_array[0]);
    this->control_widget->vertical->addWidget(this->control_widget->widget_array[1]);
    this->control_widget->widget_array[1]->show();
    this->ChangingTheSizeAndPositionOfTheMainWidget(this->control_widget);

}

void Main_class::ONE_DataSeriesCreatingAWidgetToSelect()
{
    this->result_path = "Result_1";

    if (this->series_10)
    {
        delete this->series_10;
        if (this->result_10) delete this->result_10;
        this->result_10 = nullptr;
        this->series_10 = nullptr;
        this->control_widget->widget_array[2] = nullptr;
    }

    if (this->series_1 == nullptr)
    {
        this->series_1 = new Series_1();
       

        QObject::connect(&this->series_1->buttons[0], &QPushButton::clicked, this, [this]() {

            this->control_widget->hide();
            this->MarkingPoints->show();

            });

        QObject::connect(&this->series_1->buttons[1], &QPushButton::clicked, this, &Main_class::CreatingAWidgetToDisplay_RESULT_For_ONE_Series);

    }

    this->control_widget->widget_array[1] = this->series_1;
}

void Main_class::TEN_DataSeriesCreatingAWidgetToSelect()
{
    this->result_path = "Result_10";

    if (this->series_1)
    {
        delete this->series_1;
        if (this->result_1) delete this->result_1;
        this->result_1 = nullptr;
        this->series_1 = nullptr;
        this->control_widget->widget_array[2] = nullptr;
    }

    if (this->series_10 == nullptr)
    {
        this->series_10 = new Series_10();

       // this->control_widget->buttons[0].setEnabled(true);


        for (size_t i{ 0 }; i < 10; i++)
        {
            QObject::connect(this->series_10->boxs_data[i].button, &QPushButton::clicked, [this]() {

                this->control_widget->hide();
                this->MarkingPoints->show();
                });
        }

        QObject::connect(this->series_10->button_for_calculate, &QPushButton::clicked, this, &Main_class::CreatingAWidgetToDisplay_RESULTS_sFor_TEN_Series);
    }
   
    this->control_widget->widget_array[1] = this->series_10;
}

void Main_class::CreatingAWidgetToDisplay_RESULT_For_ONE_Series()
{

    if (this->result_1 == nullptr)
    {
        this->result_1 = new Result_1();

        this->control_widget->widget_array[2] = this->result_1;
    }

    this->control_widget->current_widget++;
    this->control_widget->vertical->removeWidget(this->control_widget->widget_array[1]);
    this->control_widget->vertical->addWidget(this->control_widget->widget_array[2]);

    
    this->CalculatingTheCostOfTheRoad();
  
    this->series_1->hide();
    this->result_1->show();
    this->ChangingTheSizeAndPositionOfTheMainWidget(this->control_widget);

    
}

void Main_class::CreatingAWidgetToDisplay_RESULTS_sFor_TEN_Series()
{

    if (this->result_10 == nullptr)
    {
        this->result_10 = new Result_10();
        this->control_widget->widget_array[2] = this->result_10;
    }

    this->control_widget->current_widget++;
    this->control_widget->vertical->removeWidget(this->control_widget->widget_array[1]);
    this->control_widget->vertical->addWidget(this->control_widget->widget_array[2]);

    
    this->CalculatingTheCostOfTheRoad();
   
    this->series_10->hide();
    this->result_10->show();

    this->ChangingTheSizeAndPositionOfTheMainWidget(this->control_widget);
}

void Main_class::AcceptanceOfMarkedPoints()
{
    this->MarkingPoints->hide();
    this->control_widget->show();

    if (this->series_1)
    {
        for (size_t i{ 0 }; i < 3; i++)
        {
            this->series_1->left_box.edit[i].setText(this->MarkingPoints->BoxsForMarkBeginAndEndPoint[1].edit[i].text());
            this->series_1->right_box.edit[i].setText(this->MarkingPoints->BoxsForMarkBeginAndEndPoint[0].edit[i].text());
        }
    }
    else
    {
        this->series_10->show();

        for (size_t i{ 0 }; i < 3; i++)
        {
            this->series_10->boxs_data[this->series_10->button_number].begin_labels[i].setText(this->MarkingPoints->BoxsForMarkBeginAndEndPoint[0].edit[i].text());
            this->series_10->boxs_data[this->series_10->button_number].end_labels[i].setText(this->MarkingPoints->BoxsForMarkBeginAndEndPoint[1].edit[i].text());
        }
    }

}

void Main_class::CalculatingTheCostOfTheRoad()
{
    Algorithm_base* PerformingCalculations = nullptr;

    if (this->control_widget->begin_widget->check_2[0].isChecked())
    {
        //this->result_path += "//Result_D";

        PerformingCalculations = new  Algorithm_base(0); // 0 - means dikstra algorithm
        PerformingCalculations->result_path = this->result_path + "//Result_D";

    }
    else if (this->control_widget->begin_widget->check_2[1].isChecked())
    {
        //this->result_path += "//Result_T";

        PerformingCalculations = new  Algorithm_base(1); // 1 - means the A* algorithm, where sorting is based on the sum of the real value and the Eucleidean distance
        PerformingCalculations->result_path = this->result_path + "//Result_T";
    }

    else if (this->control_widget->begin_widget->check_2[2].isChecked())
    {
        //this->result_path += "//Result_E";

        PerformingCalculations = new  Algorithm_base(2); // 2 - means the A* algorithm, where sorting is based on the Eucleidean distance

        PerformingCalculations->result_path = this->result_path + "//Result_E";
    }

        if (this->series_10)
        {
            this->result_10->files_path = PerformingCalculations->result_path + "//Series_";

            double SumOfEucleideanDistances{ 0.0 };
            
            int NumberOfCountedSeries = { 0 };
           
            this->result_10->ReamoveImageFromFolder();
            this->result_10->current_series = 0;
            this->result_10->max_series = -1;
            float RoadCost{ 0.0 };

            for (size_t i{ 0 }; i < 10; i++)
            {
                for (size_t j{ 0 }; j < 3; j++)
                {
                    this->StartingPoint[j] = this->series_10->boxs_data[i].begin_labels[j].text().toInt();
                    this->EndPoint[j] = this->series_10->boxs_data[i].end_labels[j].text().toInt();

                }

                if (PerformingCalculations->Reload(this->StartingPoint, this->EndPoint))
                {
                    RoadCost = 0.0;

                    PerformingCalculations->result_path = this->result_10->files_path  + QString::number(i);
                   
                    PerformingCalculations->Executive();

                    SumOfEucleideanDistances += EucleideanDistanceCalculation();
                    
                    RoadCost = PerformingCalculations->nodes[this->EndPoint[2]][this->EndPoint[0]][this->EndPoint[1]].real;
                    this->result_10->max_series++;
                    this->result_10->series_array[this->result_10->max_series] = i;
                    this->result_10->series_labels[this->result_10->max_series].setText("Series " + QString::number(i + 1) + " : " + QString::number(RoadCost *50) +" [nm]");
                    this->result_10->series_labels[this->result_10->max_series].setStyleSheet("background-color: white; border : 2px solid grey;");

                    this->result_10->NumberOfVisitedNodesArray[this->result_10->max_series] = PerformingCalculations->NumberOfVisitedNodes;
                    

                    NumberOfCountedSeries++;
                    this->AverageRoadCost += RoadCost;

                }
            }

            if (NumberOfCountedSeries > 0)
            {
                this->AverageRoadCost = this->AverageRoadCost / NumberOfCountedSeries;

                double AverageEucleideanDistances = SumOfEucleideanDistances / NumberOfCountedSeries;
                double GeometricTortuosity = this->AverageRoadCost / AverageEucleideanDistances;

                this->result_10->main_result->LayoutForResult.setText("Average path cost: " + QString::number(this->AverageRoadCost * 50) + " [nm]");
                this->result_10->main_result->LayoutForResult.setFixedSize(240, 25);
                this->result_10->main_result->LayoutForResult.setStyleSheet("background-color: white; border : 2px solid blue; font-weight: bold;");

                this->result_10->main_result->LayoutForGeometricTortuosity.setText("Geometric tortuosity: " + QString::number(GeometricTortuosity));
                this->result_10->main_result->LayoutForGeometricTortuosity.setStyleSheet("background-color: white; border : 2px solid blue; font-weight: bold;");

                this->result_10->main_result->LayoutForNumberOfVisitedNodes.setStyleSheet("background-color: white; border : 2px solid green; font-weight: bold;");
               
                for (int i = this->result_10->max_series; i < 9; i++)
                {
                    this->result_10->series_labels[this->result_10->current_series].setStyleSheet("background-color: white; border : 2px solid red; font-weight: bold;");
                }


                this->result_10->ChangingTheDisplayedImage();
            }
            else
            {
                this->result_10->SettingLayoutStylesIfNotCorrectResults();
           
            }
        }
        else
        {
            this->result_1->files_path = PerformingCalculations->result_path;
            this->result_1->image_reamove();

            for (size_t i{ 0 }; i < 3; i++)
            {
                this->StartingPoint[i] = this->series_1->right_box.edit[i].text().toInt();
                this->EndPoint[i] = this->series_1->left_box.edit[i].text().toInt();
            }

            if (PerformingCalculations->Reload(this->StartingPoint, this->EndPoint))
            {
               
                PerformingCalculations->Executive();
                this->AverageRoadCost = PerformingCalculations->nodes[this->EndPoint[2]][this->EndPoint[0]][this->EndPoint[1]].real ;

                this->result_1->LayoutForResult.setText("Path cost: " + QString::number(this->AverageRoadCost * 50) +" [nm]");

                double GeometricTortuosity = this->AverageRoadCost / EucleideanDistanceCalculation();
                unsigned long int NumberOfVisitedNodes = PerformingCalculations->NumberOfVisitedNodes;

                this->result_1->LayoutForGeometricTortuosity.setText("Geometric tortuosity: " + QString::number(GeometricTortuosity));

                this->result_1->LayoutForNumberOfVisitedNodes.setText("Visited Nodes: " + QString::number(NumberOfVisitedNodes));
            }
            
            this->result_1->image_reload();
        }

    delete  PerformingCalculations;
}

double Main_class::EucleideanDistanceCalculation()
{
    double EucleideanDistance{ 0.0 };

    for (size_t j{ 0 }; j < 3; j++)
    {
        int CoordinateDifference = this->StartingPoint[j] - this->EndPoint[j];
        EucleideanDistance += CoordinateDifference * CoordinateDifference;
    }
    return std::sqrt(EucleideanDistance);
}

Main_class::~Main_class()
{
    if (MarkingPoints) delete MarkingPoints;
    if (series_1) delete series_1;
    if (result_1) delete result_1;
    if (series_10) delete series_10;
    if (result_10) delete result_10;
   
    if (control_widget) delete control_widget;
}