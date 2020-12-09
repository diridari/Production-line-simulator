//
// Created by basti on 16.11.2020.
//

#include "GuiSensor.h"
#include "MainWindow.h"
#include <QLabel>
#include <src/workpiece/Placing.h>

QPoint GuiSensor::getPos(QPoint BaseOffset, uint32_t baseWidgetSizeX, uint32_t baseWidgetSizeY) {
    // Calculate the pos depending of station direction
    guiPos p = Placing::calculateGuiPosition(connectedSensor->getSensorPos(), station);
    uint32_t posX = 0;
    uint32_t posY = 0;
    //posX = BaseOffset.x() + (baseWidgetSizeX/100) * p.posX - width()/2;
    //posY = BaseOffset.y() +(baseWidgetSizeY/100) * p.posY - height()/2;
    switch (station->getOutputDirection()) {
        case directionUp:         posY = BaseOffset.y() +(baseWidgetSizeY/100) * p.posY - height()/2; break;
        case directionDown:       posY = BaseOffset.y() +(baseWidgetSizeY/100) * p.posY - height()/2; break;
        case directionRight:      posX = BaseOffset.x() + (baseWidgetSizeX/100) * p.posX - width()/2;break;
        case directionLeft:       posX = BaseOffset.x() + (baseWidgetSizeX/100) * p.posX - width()/2; break;
    }

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
    switch (station_->getOutputDirection()) {
        case directionUp:         BaseOffset = QPoint(0,- l->height()/2);      break;
        case directionDown:       BaseOffset = QPoint(0,+ l->height()/2);      break;
        case directionRight:      BaseOffset = QPoint(-l->width()/2,0);      break;
        case directionLeft:       BaseOffset = QPoint(-l->width()/2,0);      break;
    }
    l->setPixmap(QPixmap(connectedSensor->getSensOffImage().c_str()).scaled(MinStationSize/4,MinStationSize/4,Qt::KeepAspectRatio));
    l->move(getPos(BaseOffset,parent->width(),parent->height()));
    l->show();
}

void GuiSensor::update() {

    if(connectedSensor->getSensorState() != lastState){
        lastState = connectedSensor->getSensorState();
        QWidget *parrent = (QWidget*)this->parent();
        if(lastState == SENSOR_ON){
            l->setPixmap(QPixmap(connectedSensor->getSensOnImage().c_str()).scaled(MinStationSize/4,MinStationSize/4,Qt::KeepAspectRatio));

        }else{
            l->setPixmap(QPixmap(connectedSensor->getSensOffImage().c_str()).scaled(MinStationSize/4,MinStationSize/4,Qt::KeepAspectRatio));
        }
    }
    


}
