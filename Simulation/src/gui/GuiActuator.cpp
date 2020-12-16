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
    actuatorSize = QSize(parent->width()/4,parent->height()/4);
    if(connectedActuator_->getActuatorKind() == actuatorKind::Pusher) {
        switch (station_->getOutputDirection()) {
            case directionUp:
                actuatorSize = QSize(parent->width(),parent->height()/8);
                break;
            case directionDown:
                actuatorSize = QSize(parent->width(),parent->height()/8);
                break;
            case directionRight:
                actuatorSize = QSize( parent->width()/8,parent->height());
                break;
            case directionLeft:
                actuatorSize = QSize( parent->width()/8,parent->height());
                break;
        }
    }
    setMinimumSize(actuatorSize);
    l->setPixmap(QPixmap(connectedActuator->getActuatorImage().c_str()).scaled(actuatorSize,Qt::IgnoreAspectRatio).transformed(rot));
    l->setMinimumSize(actuatorSize);
    show();
    move(getPos(BaseOffset,parent->width(),parent->height()));


}

void GuiActuator::update() {
    QWidget *parent =(QWidget*) parentWidget();

    if(connectedActuator->getActuatorImage() != lastImg){
        lastImg =  connectedActuator->getActuatorState();
        l->setPixmap(QPixmap(connectedActuator->getActuatorImage().c_str()).scaled(actuatorSize,Qt::IgnoreAspectRatio).transformed(rot));
    }
    if(connectedActuator->getActuatorKind() == actuatorKind::Pusher) {
        switch (station->getOutputDirection()) {
            case directionUp:
                actuatorSize = QSize(parent->width(),parent->height()/8);
                break;
            case directionDown:
                actuatorSize = QSize(parent->width(),parent->height()/8);
                break;
            case directionRight:
                actuatorSize = QSize( parent->width()/8,parent->height());
                break;
            case directionLeft:
                actuatorSize = QSize( parent->width()/8,parent->height());
                break;
        }
    }
    move(getPos(BaseOffset,parent->width(),parent->height()));
    show();


}

QPoint GuiActuator::getPos(QPoint BaseOffset_, uint32_t baseWidgetSizeX, uint32_t baseWidgetSizeY) {
    // Calculate the pos depending of station direction
    guiPos p = Placing::calculateGuiPosition(connectedActuator->getPosition(), station);
    switch (connectedActuator->getActuatorKind()) {
        case actuatorKind::Pusher:
              switch (station->getOutputDirection()) {
                    case directionUp:         rot = QTransform().rotate(270); BaseOffset = QPoint(0,-this->height());
                      //p = guiPos(0,100-connectedActuator->getPosition()*0.8);
                      p.posX = 0;
                    break;
                    case directionDown:       rot = QTransform().rotate(90);  BaseOffset = QPoint(0,-this->height()*2);
                      //p = guiPos(0,connectedActuator->getPosition()*0.8);
                      p.posX = 0;
                      break;
                    case directionRight:      rot = QTransform().rotate(0);   BaseOffset = QPoint(-this->width(),0);
                     // p = guiPos(connectedActuator->getPosition()*0.8,0);
                      p.posY = 0;
                      break;
                    case directionLeft:       rot = QTransform().rotate(180); BaseOffset = QPoint(this->width(),0);
                     // p = guiPos(100-connectedActuator->getPosition()*0.8,0);
                      p.posY = 0;
                      break;

                 }break;
        case actuatorKind::MillerDrill :
                switch (station->getOutputDirection()) {
                    case directionUp:         rot = QTransform().rotate(270); BaseOffset = QPoint(0,-this->height()/2); p.posX = 100;     break;
                    case directionDown:       rot = QTransform().rotate(90);  BaseOffset = QPoint(0,-this->height()/2); p.posX = 0;     break;
                    case directionRight:      rot = QTransform().rotate(0);   BaseOffset = QPoint(-this->width()/2,0); p.posY = 0;     break;
                    case directionLeft:       rot = QTransform().rotate(180); BaseOffset = QPoint(-this->width()/2,0); p.posY = 100;    break;
                }
            break;
        case actuatorKind::Conveyorbelt_ :
                switch (station->getOutputDirection()) {
                        case directionUp:         rot = QTransform().rotate(270); BaseOffset = QPoint(-this->width()/2,+ this->height()/2);  p.posX = 50;     break;
                        case directionDown:       rot = QTransform().rotate(90);  BaseOffset = QPoint(-this->width()/2,- this->height()/2);  p.posX = 50;     break;
                        case directionRight:      rot = QTransform().rotate(0);   BaseOffset = QPoint(-this->width()*1,-this->height()/2);   p.posY = 50;    break;
                        case directionLeft:       rot = QTransform().rotate(180); BaseOffset = QPoint(this->width()/2,-this->height()/2);    p.posY = 50;   break;
                }
            break;
    }

    uint32_t posX,posY;
    posX = BaseOffset.x() + (parentWidget()->width()/100) * p.posX;
    posY = BaseOffset.y() +(parentWidget()->height()/100) * p.posY; // move by widget size to the left
    return QPoint(posX,posY);
}


