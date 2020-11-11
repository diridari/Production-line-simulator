//
// Created by basti on 11.11.2020.
//

#ifndef PRODUCTION_LINE_SIMULATOR_GUIBOX_H
#define PRODUCTION_LINE_SIMULATOR_GUIBOX_H


#include <src/productionStation/BaseProductionStation.h>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include "GuiStation.h"

class GuiBox : public QWidget{
    BaseWorkpiece *connectedWorkpiece;
    GuiStation *currentStation; // determine abs pos + direction of movement
    uint32_t AbsPosX,AbsPosY;
    QLabel *l;
public:
    GuiBox( BaseWorkpiece *connectedWorkpiece, GuiStation * currentStation, QWidget *parent = nullptr);
    void updateBoxPos();
    void setStation(GuiStation *gs);;

};



#endif //PRODUCTION_LINE_SIMULATOR_GUIBOX_H
