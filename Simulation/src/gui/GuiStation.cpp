//
// Created by basti on 11.11.2020.
//
#include <src/main.h>
#include "MainWindow.h"
#include "GuiStation.h"
#include <QPushButton>

void GuiStation::setPosition(int posX_, int posY_) {
    Log::log("gui: set Position of " + connectedStation->getStationName() + " to x:" + to_string(posX_) + " , y:"+ to_string(posY_),Info);
    posX = posX_;
    posY = posY_;
}
Direction GuiStation::getInputDirection() {
    return inputDirection;
}

Direction GuiStation::getOutputDirection() {
    return outputDirection;
}

GuiStation::GuiStation(BaseProductionStation *connectedStation, Direction inputDirection, Direction outputDirection,
                       QWidget *parent): QWidget(parent),outputDirection(outputDirection),inputDirection(inputDirection),connectedStation(connectedStation) {
    Log::log("create new Gui Station for "+ connectedStation->getStationName(),Info);
    l = new QLabel(this);
    l->setPixmap(QPixmap("../img/BaseStation.png").scaled(MinStationSize,MinStationSize,Qt::KeepAspectRatio));
    setMinimumSize(MinStationSize,MinStationSize);
    l->setScaledContents(true);
    // Change actuator State Button
    QPushButton *stationActuator = new QPushButton(this);
    stationActuator->setText("set Actuator State ");
    stationActuator->move(this->size().width()-stationActuator->size().width(), 0);
    stationActuator->show();
    connect(stationActuator, SIGNAL(clicked()), this, SLOT(GuiStation::updateActuatorState()));
    connect(stationActuator, SIGNAL(clicked()), this, SLOT(whenButtonIsClicked()));


    // PrintState Text
    stationState = new QLabel(this);
    stationState->setScaledContents(true);
    stationState->setText("station State gets updated on first Frame");
    stationState->adjustSize();
    stationState->show();

}

void GuiStation::handleBoxes() {
    Log::log("update gui for station "+ connectedStation->getStationName(),Debug);
    vector<BaseWorkpiece*> * boxes = connectedStation->getBoxesOnStation();
    for(int i = 0; i< boxes->size();i++){
        BaseWorkpiece *wp = boxes->at(i);
        GuiBox *gb = objectMapper->getGuiBox(wp);
        if(gb == nullptr){
            Log::log("found no matching gui box --> create new one ",Info);
            gb = new GuiBox(wp,this->parentWidget());
            gb->show();
            objectMapper->addBox(wp,gb);
        }
        uint32_t widgetSize = this->size().height();
        uint32_t posX,posY;
        posX = this->pos().x() + (widgetSize/100)*wp->getPosition();
        posY = this->pos().y() +widgetSize/2;
        gb->move(posX,posY);
    }

    // Update State text
    Log::log("update Station Sates on Gui",DebugL2);
    string stationStateText = "station State :\r\n";
    vector<BaseActuator *>* actators = connectedStation->getActuators();
    vector<BaseSensor *>* sensors = connectedStation->getSensors();
    for(int i = 0; i <actators->size();i++){
        stationStateText += actators->at(i)->getActuatorName() + " :" +  to_string(actators->at(i)->getActuatorState()) +"\r\n";
    }
    for(int i = 0; i <sensors->size();i++){
        stationStateText += sensors->at(i)->getSensorState() + " :" +  to_string(sensors->at(i)->getSensorState()) +"\r\n";
    }
    Log::log("current station state: " + stationStateText, DebugL3)
    stationState->setText(stationStateText.c_str());
    stationState->adjustSize();
    stationState->show();

}

void GuiStation::updateActuatorState() {
    Log::log("gui change actuator state for "+connectedStation->getStationName(),Info);
    connectedStation->getActuators()->at(0)->toogleState();
}

void GuiStation::whenButtonIsClicked() {

}

