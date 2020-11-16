//
// Created by basti on 16.11.2020.
//

#include "GuiSensor.h"

QPoint
GuiSensor::getPos(QPoint BaseOffset, uint32_t baseWidgetSizeX, uint32_t baseWidgetSizeY, Direction inputDirection,
                  Direction outputDirection) {
    uint32_t posX,posY;
    QPoint p;
    uint8_t  pos = connectedSensor->getSensorPos();
    // Calculate the pos depending of station direction
    if(pos <= 50){
        switch (inputDirection) {
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

GuiSensor::GuiSensor(BaseSensor *connectedSensor_, QWidget *parent, Direction inputDirection,
                     Direction outPutDirection) : QWidget(parent) {
    connectedSensor = connectedSensor_;
    l = new QLabel(this);
    l->setPixmap(QPixmap(SensorOFFIMG).scaled(parent->height()/5,parent->width()/5,Qt::KeepAspectRatio));
    l->move(getPos(QPoint(0,0),parent->width(),parent->height(),inputDirection,outPutDirection));
}

void GuiSensor::update() {

    if(connectedSensor->getSensorState() != lastState){
        lastState = connectedSensor->getSensorState();
        QWidget *parrent = (QWidget*)this->parent();
        if(lastState == SENSOR_ON){
            l->setPixmap(QPixmap(SensorONIMG).scaled(parrent->height()/5,parrent->width()/5,Qt::KeepAspectRatio));

        }else{
            l->setPixmap(QPixmap(SensorOFFIMG).scaled(parrent->height()/5,parrent->width()/5,Qt::KeepAspectRatio));
        }
    }
}
