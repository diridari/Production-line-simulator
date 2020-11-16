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

QPoint GuiBox::getNewPos(QPoint BaseOffset, uint32_t baseWidgetSizeX, uint32_t baseWidgetSizeY,Direction inPutDirection, Direction outputDirection ) {
    uint32_t posX,posY;
    QPoint p;
    uint8_t  pos = connectedWorkpiece->getPosition();
    // Calculate the pos depending of station direction
    if(pos <= 50){
        switch (inPutDirection) {
            case directionUp    : posX = 50; posY = pos;        break;
            case directionDown  : posX = 50; posY = 100-pos;    break;
            case directionLeft  : posX = pos; posY = 50;        break;
            case directionRight : posX = 100- pos; posY = 50;   break;
        }
    }else {
        switch (outputDirection) {
            case directionUp    : posX = 50; posY = 100-pos;    break;
            case directionDown  : posX = 50; posY = pos;        break;
            case directionLeft  : posX = 100 - pos; posY = 50;  break;
            case directionRight : posX = pos; posY = 50;        break;
        }

    }

    posX = BaseOffset.x() + (baseWidgetSizeX/100) * posX;
    posY = BaseOffset.y() +(baseWidgetSizeY/100) * posY;
    return QPoint(posX,posY);

}

void GuiBox::moveToNewPos(QPoint BaseOffset, uint32_t baseWidgetSizeX, uint32_t baseWidgetSizeY,Direction inPutDirection,Direction outputDirection) {
    move(getNewPos(BaseOffset,baseWidgetSizeX,baseWidgetSizeY,inPutDirection,outputDirection));
}

