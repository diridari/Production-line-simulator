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
    l->setPixmap(QPixmap(connectedActuator->getActuatorImage().c_str()).scaled(parent->height()/5,parent->width()/5,Qt::KeepAspectRatio).transformed(rot));
    setMinimumSize(parent->height()/5,parent->width()/5);
    move(getPos(BaseOffset,parent->width(),parent->height()));
    show();

}

void GuiActuator::update() {
    QWidget *parent =(QWidget*) parentWidget();

    if(connectedActuator->getActuatorImage() != lastImg){
        lastImg =  connectedActuator->getActuatorState();
        l->setPixmap(QPixmap(connectedActuator->getActuatorImage().c_str()).scaled(parent->width()/5,parent->height()/5,Qt::IgnoreAspectRatio).transformed(rot));
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
                    case directionUp:         rot = QTransform().rotate(270); BaseOffset = QPoint(-this->width()/2,+ this->height()*1);      break;
                    case directionDown:       rot = QTransform().rotate(90);  BaseOffset = QPoint(this->width()/2,- this->height()/2);      break;
                    case directionRight:      rot = QTransform().rotate(0);   BaseOffset = QPoint(-this->height()/2,-this->height()/2);      break;
                    case directionLeft:       rot = QTransform().rotate(180); BaseOffset = QPoint(this->width()/2,-this->height()/2);      break;

                 }break;
        case actuatorKind::MillerDrill :
            if(connectedActuator->getPosition() < 33){
                switch (station->getInputDirection()) {
                    case directionUp:         rot = QTransform().rotate(270); BaseOffset = QPoint(-this->width(),-this->height()/2);      break;
                    case directionDown:       rot = QTransform().rotate(270);  BaseOffset = QPoint(-this->width(),-this->height()/2);      break;
                    case directionRight:      rot = QTransform().rotate(0);   BaseOffset = QPoint(-this->width()/2,-this->height());      break;
                    case directionLeft:       rot = QTransform().rotate(180); BaseOffset = QPoint(-this->width()/2,this->height());      break;
                }
            }else{
                switch (station->getOutputDirection()) {
                    case directionUp:         rot = QTransform().rotate(270); BaseOffset = QPoint(-this->width(),-this->height()/2);      break;
                    case directionDown:       rot = QTransform().rotate(90);  BaseOffset = QPoint(+this->width()/2,-this->height()/2);      break;
                    case directionRight:      rot = QTransform().rotate(0);   BaseOffset = QPoint(-this->width()/2,-this->height());      break;
                    case directionLeft:       rot = QTransform().rotate(180); BaseOffset = QPoint(-this->width()/2,this->height()/2);      break;
                }
            }break;
        case actuatorKind::Conveyorbelt_ :
            if(connectedActuator->getPosition() < 33){
                switch (station->getInputDirection()) {
                    case directionUp:         rot = QTransform().rotate(270); BaseOffset = QPoint(-this->width()/2,+ this->height()*1);      break;
                    case directionDown:       rot = QTransform().rotate(90);  BaseOffset = QPoint(-this->width()/2,- this->height()*2);      break;
                    case directionRight:      rot = QTransform().rotate(0);   BaseOffset = QPoint(-this->width()*1,-this->height()/2);      break;
                    case directionLeft:       rot = QTransform().rotate(180); BaseOffset = QPoint(this->width()/2,-this->height()/2);      break;
                }
            }else{
                switch (station->getOutputDirection()) {
                    case directionUp:         rot = QTransform().rotate(270); BaseOffset = QPoint(-this->width()/2,+ this->height()*1);      break;
                    case directionDown:       rot = QTransform().rotate(90);  BaseOffset = QPoint(-this->width()/2,- this->height()*2);      break;
                    case directionRight:      rot = QTransform().rotate(0);   BaseOffset = QPoint(-this->width()*1,-this->height()/2);      break;
                    case directionLeft:       rot = QTransform().rotate(180); BaseOffset = QPoint(this->width()/2,-this->height()/2);      break;
                }
            }break;
    }

    uint32_t posX,posY;
    posX = BaseOffset.x() + (parentWidget()->width()/100) * p.posX;
    posY = BaseOffset.y() +(parentWidget()->height()/100) * p.posY; // move by widget size to the left
    return QPoint(posX,posY);
}
