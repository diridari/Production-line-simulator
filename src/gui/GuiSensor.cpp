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
    switch (station->getOutputDirection()) {
        case directionUp:         posY = BaseOffset.y() +(baseWidgetSizeY/100) * p.posY;  posX=baseWidgetSizeX - l->width(); break;
        case directionDown:       posY = BaseOffset.y() +(baseWidgetSizeY/100) * p.posY;  posX=0;   break;
        case directionRight:      posX = BaseOffset.x() + (baseWidgetSizeX/100) * p.posX; posY=baseWidgetSizeY - l->height(); break;
        case directionLeft:       posX = BaseOffset.x() + (baseWidgetSizeX/100) * p.posX; posY=0;   break;
    }
    return QPoint(posX,posY);
}

GuiSensor::GuiSensor(BaseSensor *connectedSensor_, BaseProductionStation *station_, QWidget *parent) : QWidget(parent) {
    connectedSensor = connectedSensor_;
    station = station_;
    Log::log("create gui sensor "+ connectedSensor->getSensorName() + " on station " + station_->getStationName(),Info);
    l = new QLabel(this);
   // setMinimumSize(parent->height()/5,parent->width()/5);

    QPixmap *p = new QPixmap(connectedSensor->getSensOffImage().c_str());
    if( p->isNull()){
        string s = "../" + connectedSensor->getSensOffImage();
        p = new QPixmap(s.c_str());
        if( p->isNull()){
            Log::log("Failed to open box image",Error);
            exit (-11);
        }
    }
    l->setPixmap(p->scaled(MinStationSize/4,MinStationSize/4,Qt::IgnoreAspectRatio));
    //setMinimumSize(MinStationSize/4,MinStationSize/4);
    //l->setMinimumSize(MinStationSize/4,MinStationSize/4);
    l->show();
    QPoint BaseOffset = QPoint(-l->width()/2,-l->height()/2);
    l->move(getPos(BaseOffset,parent->width(),parent->height()));
}

void GuiSensor::update() {


    if(connectedSensor->getSensorState() != lastState){
        string s;
        lastState = connectedSensor->getSensorState();
        if(lastState == SENSOR_ON){
            s = connectedSensor->getSensOnImage();
        }else{
            s = connectedSensor->getSensOffImage();
        }
        QPixmap *p = new QPixmap(s.c_str());
        if( p->isNull()){
            string ns = "../" + s;
            p = new QPixmap(ns.c_str());
            if( p->isNull()){
                Log::log("Failed to open sensor image " + s,Error);
                exit (-11);
            }
        }
        l->setPixmap(p->scaled(l->width(),l->height(),Qt::IgnoreAspectRatio));

    }
    l->move(getPos(QPoint(-l->width()/2,-l->height()/2),parentWidget()->width(),parentWidget()->height()));



}
