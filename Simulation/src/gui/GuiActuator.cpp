//
// Created by basti on 17.11.2020.
//

#include "GuiActuator.h"
#include <QLabel>
#include <QWidget>
#include <src/workpiece/Placing.h>
#include <src/actuators/pusher.h>

GuiActuator::GuiActuator(BaseActuator *connectedActuator_, BaseProductionStation *station_, QWidget *parent): QWidget(parent)  {
    if(connectedActuator_ == nullptr)
        Log::log("received nullpntr",Error);
    if(station_ == nullptr)
        Log::log("received nullpntr",Error);
    Log::log("create Gui Actuator: "+ connectedActuator_->getActuatorName(),Info);
    BaseOffset = QPoint(0,0);
    connectedActuator = connectedActuator_;
    station = station_;
    l = new QLabel(this);
    l->setScaledContents(true);
    l->setPixmap(QPixmap(connectedActuator->getActuatorImage().c_str()).scaled(parent->height()/5,parent->width()/5,Qt::KeepAspectRatio));
    setMinimumSize(parent->height()/5,parent->width()/5);
    move(getPos(BaseOffset,parent->width(),parent->height()));
    show();

}

void GuiActuator::update() {
    QWidget *parent =(QWidget*) parentWidget();

    if(connectedActuator->getActuatorImage() != lastImg){
        lastImg =  connectedActuator->getActuatorState();
        l->setPixmap(QPixmap(connectedActuator->getActuatorImage().c_str()).scaled(parent->height()/5,parent->width()/5,Qt::IgnoreAspectRatio));
    }
    move(getPos(BaseOffset,parent->height(),parent->width()));
    show();


}

QPoint GuiActuator::getPos(QPoint BaseOffset, uint32_t baseWidgetSizeX, uint32_t baseWidgetSizeY) {
    // Calculate the pos depending of station direction
    guiPos p = Placing::calculateGuiPosition(connectedActuator->getPosition(), station);
    uint32_t posX,posY;
    posX = BaseOffset.x() + (baseWidgetSizeX/100) * p.posX-this->width();
    posY = BaseOffset.y() +(baseWidgetSizeY/100) * p.posY -this->height() ; // move by widget size to the left
    return QPoint(posX,posY);
}
