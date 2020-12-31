//
// Created by basti on 11.11.2020.
//

#ifndef PRODUCTION_LINE_SIMULATOR_MAINWINDOW_H
#define PRODUCTION_LINE_SIMULATOR_MAINWINDOW_H
#include <QMainWindow>
#include <QtWidgets/QLabel>
#include <src/productionStation/BaseProductionStation.h>
#include "GuiBox.h"
#include "GuiStation.h"
#include <QtWidgets/QGridLayout>
#include <QMouseEvent>


#define MinStationSize 150
class MainWindow :public QWidget{
Q_OBJECT
    BaseProductionStation * startStation;
    vector<GuiBox*> *boxSet = new vector<GuiBox*>();
    vector<GuiStation*> *stationSet = new vector<GuiStation*>();


public:
    MainWindow(BaseProductionStation *startStation, QWidget *parent = nullptr);
    bool dropBox(BaseWorkpiece *wp);
    uint8_t gridSizeX = 1,gridSizeY=1;

public slots:
    void update();
    void resizeEvent( QResizeEvent *e) override;
};


#endif //PRODUCTION_LINE_SIMULATOR_MAINWINDOW_H
