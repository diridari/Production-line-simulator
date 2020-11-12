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

class MainWindow :public QWidget{
    BaseProductionStation * startStation;
    vector<GuiBox*> *boxSet;
    QVBoxLayout *mainLayout;
    QGridLayout *gridLayout;
public:
    MainWindow(QWidget *parent = nullptr);
    QWidget *mainWidget;

    GuiBox * addBox(BaseWorkpiece * wp,GuiStation *guiStation){

        if(guiStation == nullptr || wp == nullptr){
            Log::log("gui add Box received nullpntr",Error);
            return nullptr;
        }
       GuiBox * b = new GuiBox(wp,guiStation);

       b->show();
       boxSet->push_back(b);
       return b;

    }

    GuiStation * addStation(BaseProductionStation *ps) {
        if (ps == nullptr) {
            Log::log("gui add station received nullpntr",Error);
        }
        GuiStation * s = new GuiStation(ps);
        insertWidget(s);
        return s;
    }
    void insertWidget(QWidget *w){
        static int x = 0;
        gridLayout->addWidget(w,x,x,1,1);
        w->show();
        this->show();
        x++;
    }
public slots:

    void update();
};


#endif //PRODUCTION_LINE_SIMULATOR_MAINWINDOW_H
