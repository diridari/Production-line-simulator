//
// Created by basti on 11.11.2020.
//

#include "GuiStation.h"

GuiStation::GuiStation(BaseProductionStation *connectedStation, QLabel *parent): QLabel(parent), connectedStation(connectedStation) {

   setPixmap(QPixmap("../img/BaseStation.png").scaled(200,200,Qt::KeepAspectRatio));
   setScaledContents(true);
}
