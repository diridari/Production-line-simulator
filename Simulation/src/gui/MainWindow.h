//
// Created by basti on 11.11.2020.
//

#ifndef PRODUCTION_LINE_SIMULATOR_MAINWINDOW_H
#define PRODUCTION_LINE_SIMULATOR_MAINWINDOW_H
#include <QMainWindow>
#include <QtWidgets/QLabel>
#include <src/productionStation/BaseProductionStation.h>
#include "GuiBox.h"
#include <QtWidgets/QGridLayout>


#define MinStationSize 300
class MainWindow :public QWidget{
    BaseProductionStation * startStation;
    vector<GuiBox*> *boxSet;
    vector<GuiStation*> *stationSet;
public:
    MainWindow(BaseProductionStation *startStation, QWidget *parent = nullptr);


public slots:

    void update();
};


#endif //PRODUCTION_LINE_SIMULATOR_MAINWINDOW_H
