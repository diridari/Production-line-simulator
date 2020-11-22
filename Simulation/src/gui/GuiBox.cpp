//
// Created by basti on 11.11.2020.
//

#include "GuiBox.h"
#include "MainWindow.h"
#include <src/workpiece/Placing.h>
#include <src/main.h>

GuiBox::GuiBox( BaseWorkpiece *connectedWorkpiece, QWidget *parent_):
        QWidget(parent_),connectedWorkpiece(connectedWorkpiece) {
    Log::log("new gui Box for " + connectedWorkpiece->getName(),Info);
    l = new QLabel(this);
    uint32_t size = MinStationSize/100*connectedWorkpiece->getWorkpieceSize();
    l->setPixmap(QPixmap("../img/box.png").scaled(size,size,Qt::KeepAspectRatio));
    l->show();

}

QPoint GuiBox::getNewPos(QPoint BaseOffset, uint32_t baseWidgetSizeX, uint32_t baseWidgetSizeY,BaseProductionStation *station  ) {
    guiPos p = Placing::calculateGuiPosition(connectedWorkpiece, station);
    uint32_t posX,posY;
    posX = BaseOffset.x() + (baseWidgetSizeX/100) * p.posX - width()/2;
    posY = BaseOffset.y() +(baseWidgetSizeY/100) * p.posY-height()/2;
    return QPoint(posX,posY);

}

void GuiBox::moveToNewPos(QPoint BaseOffset, uint32_t baseWidgetSizeX, uint32_t baseWidgetSizeY,BaseProductionStation * station) {
    move(getNewPos(BaseOffset,baseWidgetSizeX,baseWidgetSizeY,station));
}

void GuiBox::mousePressEvent(QMouseEvent *event) {
    switch (event->button()) {
        case Qt::LeftButton :         Log::log("clicked on Box "+connectedWorkpiece->getName()+"  with left",Debug);break;
        case Qt::RightButton :         Log::log("clicked on Box"+connectedWorkpiece->getName()+"  with right --> erase box",Debug);
           // connectedWorkpiece-> ;dropBox(connectedWorkpiece);
            objectMapper->dropBox(connectedWorkpiece);
            delete this;
            break;
        default:
            Log::log("clicked on Main  with "+ to_string(event->button()),Message);break;
    }
}

