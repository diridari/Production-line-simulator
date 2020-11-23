//
// Created by basti on 16.11.2020.
//

#include "GuiSensor.h"
#include <QLabel>
#include <src/workpiece/Placing.h>

QPoint GuiSensor::getPos(QPoint BaseOffset, uint32_t baseWidgetSizeX, uint32_t baseWidgetSizeY) {
    // Calculate the pos depending of station direction
    guiPos p = Placing::calculateGuiPosition(connectedSensor->getSensorPos(), station);
    uint32_t posX,posY;
    posX = BaseOffset.x() + (baseWidgetSizeX/100) * p.posX - width()/2;
    posY = BaseOffset.y() +(baseWidgetSizeY/100) * p.posY - height()/2;

    return QPoint(posX,posY);
}

GuiSensor::GuiSensor(BaseSensor *connectedSensor_, BaseProductionStation *station_, QWidget *parent) : QWidget(parent) {
    connectedSensor = connectedSensor_;
    station = station_;
    Log::log("create gui sensor "+ connectedSensor->getSensorName() + " on station " + station_->getStationName(),Info);
    l = new QLabel(this);
   // setMinimumSize(parent->height()/5,parent->width()/5);
   QPoint BaseOffset;
   Direction direction;
   if(connectedSensor_->getSensorPos() <50)
       direction = station_->getInputDirection();
   else
       direction = station_->getOutputDirection();
    switch (direction) {
        case directionUp:         BaseOffset = QPoint(this->width(),- this->height()/2);      break;
        case directionDown:       BaseOffset = QPoint(-this->width(),- this->height()/2);      break;
        case directionRight:      BaseOffset = QPoint(0,+this->height()*2);      break;
        case directionLeft:       BaseOffset = QPoint(- this->width()/2,-this->height());      break;
    }
    l->setPixmap(QPixmap(SensorOFFIMG).scaled(parent->height()/5,parent->width()/5,Qt::KeepAspectRatio));
    l->move(getPos(BaseOffset,parent->width(),parent->height()));
    l->show();
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
