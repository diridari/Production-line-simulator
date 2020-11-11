//
// Created by basti on 11.11.2020.
//

#ifndef PRODUCTION_LINE_SIMULATOR_MAINWINDOW_H
#define PRODUCTION_LINE_SIMULATOR_MAINWINDOW_H
#include <QMainWindow>
#include <QtWidgets/QLabel>
#include <src/productionStation/BaseProductionStation.h>
#include "GuiBox.h"

void runGui(int argc, char *argv[], BaseProductionStation *startStation);
void runGui2(QApplication *app) ;
class MainWindow :public QWidget{
    BaseProductionStation * startStation;
    vector<GuiBox*> *boxSet;
public:
    MainWindow(QWidget *parent = nullptr);
    QWidget *mainWidget;

    GuiBox * addBox(BaseWorkpiece * wp,GuiStation *guiStation){
        if(guiStation == nullptr || wp == nullptr){
            Log::log("gui add Box received nullpntr",Error);
            return nullptr;
        }
        GuiBox *b = new GuiBox(wp,guiStation,mainWidget);
        b->show();
        boxSet->push_back(b);
        return b;
    }

    GuiStation * addStation(BaseProductionStation *ps) {
        if (ps == nullptr) {
            Log::log("gui add station received nullpntr",Error);
        }
        GuiStation *s = new GuiStation(ps,mainWidget);
        s->show();
        return s;
    }
public slots:

    void update();
};


#endif //PRODUCTION_LINE_SIMULATOR_MAINWINDOW_H
