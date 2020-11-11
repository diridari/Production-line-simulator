//
// Created by basti on 11.11.2020.
//

#ifndef PRODUCTION_LINE_SIMULATOR_MAINWINDOW_H
#define PRODUCTION_LINE_SIMULATOR_MAINWINDOW_H
#include <QMainWindow>
#include <QtWidgets/QLabel>
#include <src/productionStation/BaseProductionStation.h>

void runGui(int argc, char *argv[], BaseProductionStation *startStation);
class MainWindow :public QWidget{
    BaseProductionStation * startStation;
    QLabel *l1;
    QLabel *l2;
    QLabel *l3;
    QLabel *l4;
    QLabel *l5;
public:
    MainWindow(BaseProductionStation *startStation_, QWidget *parent = nullptr);

public slots:
    void update();
};



#endif //PRODUCTION_LINE_SIMULATOR_MAINWINDOW_H
