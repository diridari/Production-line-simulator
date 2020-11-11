//
// Created by basti on 11.11.2020.
//

#include "GuiStation.h"

GuiStation::GuiStation(BaseProductionStation *connectedStation, QWidget *parent): QWidget(parent), connectedStation(connectedStation) {
    l = new QLabel();
    l->setPixmap(QPixmap("../img/BaseStation.png").scaled(200,200));
    l->show();
}
