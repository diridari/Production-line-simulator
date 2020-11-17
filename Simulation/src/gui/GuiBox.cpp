//
// Created by basti on 11.11.2020.
//

#include "GuiBox.h"
#include "MainWindow.h"
#include <src/workpiece/Placing.h>

GuiBox::GuiBox( BaseWorkpiece *connectedWorkpiece, QWidget *parent):
        QWidget(parent),connectedWorkpiece(connectedWorkpiece) {
    Log::log("new gui Box for " + connectedWorkpiece->getName(),Info);
    l = new QLabel(this);
    uint32_t size = MinStationSize/100*connectedWorkpiece->getWorkpieceSize();
    l->setPixmap(QPixmap("../img/box.png").scaled(size,size,Qt::KeepAspectRatio));
    l->show();

}

QPoint GuiBox::getNewPos(QPoint BaseOffset, uint32_t baseWidgetSizeX, uint32_t baseWidgetSizeY,BaseProductionStation *station  ) {
    guiPos p = Placing::calculateGuiPosition(connectedWorkpiece, station);
    uint32_t posX,posY;
    posX = BaseOffset.x() + (baseWidgetSizeX/100) * p.posX;
    posY = BaseOffset.y() +(baseWidgetSizeY/100) * p.posY;
    return QPoint(posX,posY);

}

void GuiBox::moveToNewPos(QPoint BaseOffset, uint32_t baseWidgetSizeX, uint32_t baseWidgetSizeY,BaseProductionStation * station) {
    move(getNewPos(BaseOffset,baseWidgetSizeX,baseWidgetSizeY,station));
}

