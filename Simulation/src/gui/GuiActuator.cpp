//
// Created by basti on 17.11.2020.
//

#include "GuiActuator.h"
#include <QLabel>
#include <QWidget>
#include <src/workpiece/Placing.h>
#include <src/actuators/pusher.h>

GuiActuator::GuiActuator(BaseActuator *connectedActuator_, BaseProductionStation *station, QWidget *parent): QWidget(parent)  {
    connectedActuator = connectedActuator_;
    station = station;
    l = new QLabel(this);
    l->setPixmap(QPixmap(connectedActuator->getActuatorImage().c_str()).scaled(parent->height()/5,parent->width()/5,Qt::KeepAspectRatio));
    l->move(getPos(QPoint(0,0),parent->width(),parent->height()));
    l->show();
}

void GuiActuator::update() {

    QWidget *parent =(QWidget*) parentWidget();
    l->move(getPos(QPoint(0,0),parent->height()/5,parent->width()/5));
}

QPoint GuiActuator::getPos(QPoint BaseOffset, uint32_t baseWidgetSizeX, uint32_t baseWidgetSizeY) {
    // Calculate the pos depending of station direction
    guiPos p = Placing::calculateGuiPosition((connectedActuator)->getPosition(), station);
    uint32_t posX,posY;
    posX = BaseOffset.x() + (baseWidgetSizeX/100) * p.posX;
    posY = BaseOffset.y() +(baseWidgetSizeY/100) * p.posY;

    return QPoint(posX,posY);
}
