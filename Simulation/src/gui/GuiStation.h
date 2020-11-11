//
// Created by basti on 11.11.2020.
//

#ifndef PRODUCTION_LINE_SIMULATOR_GUISTATION_H
#define PRODUCTION_LINE_SIMULATOR_GUISTATION_H


#include <QtWidgets/QWidget>
#include <src/productionStation/BaseProductionStation.h>

class GuiStation : public QWidget{
    BaseProductionStation *connectedStation;
public:
    GuiStation(BaseProductionStation *connectedStation, QWidget *parent = nullptr);

};


#endif //PRODUCTION_LINE_SIMULATOR_GUISTATION_H
