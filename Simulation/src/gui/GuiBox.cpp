//
// Created by basti on 11.11.2020.
//

#include "GuiBox.h"
#include "MainWindow.h"

GuiBox::GuiBox( BaseWorkpiece *connectedWorkpiece, QWidget *parent):
        QWidget(parent),connectedWorkpiece(connectedWorkpiece) {
    Log::log("new gui Box for " + connectedWorkpiece->getName(),Info);
    l = new QLabel(this);
    uint32_t size = MinStationSize/100*connectedWorkpiece->getWorkpieceSize();
    l->setPixmap(QPixmap("../img/box.png").scaled(size,size,Qt::KeepAspectRatio));
    l->show();

}

