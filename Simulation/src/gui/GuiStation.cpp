//
// Created by basti on 11.11.2020.
//
#include <src/main.h>
#include "MainWindow.h"
#include "GuiStation.h"
#include "GuiSensor.h"
#include <QPushButton>

void GuiStation::setGridPosition(int posX_, int posY_) {
    Log::log("gui: set Position of " + connectedStation->getStationName() + " to x:" + to_string(posX_) + " , y:" + to_string(posY_), Info);
    gridPosX = posX_;
    gridPosY = posY_;
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
    QPixmap p;
    QTransform rot;
    // get station direction to termine picmap and rotation matrix
    if(inputDirection == directionUp && outputDirection == directionDown || inputDirection == directionDown && outputDirection ==  directionUp) {
        imagePath = "../img/BaseStation.png";
    }else if (inputDirection == directionLeft && outputDirection == directionRight || inputDirection == directionRight && outputDirection ==  directionLeft){
        imagePath = "../img/BaseStation.png";
        rot = QTransform().rotate(90);
    }else if(inputDirection == directionUp && outputDirection == directionRight || inputDirection == directionRight && outputDirection == directionUp){
        imagePath = "../img/BaseStationEdge.png";
    }else if(inputDirection == directionRight && outputDirection == directionDown || inputDirection == directionDown && outputDirection == directionRight){
        imagePath = "../img/BaseStationEdge.png";
        rot = QTransform().rotate(90);
    }else if(inputDirection == directionDown && outputDirection == directionLeft || inputDirection == directionLeft && outputDirection == directionDown){
        imagePath = "../img/BaseStationEdge.png";
        rot = QTransform().rotate(180);
    }
    else if(inputDirection == directionLeft && outputDirection == directionUp || inputDirection == directionUp && outputDirection == directionLeft){
        imagePath = "../img/BaseStationEdge.png";
        rot = QTransform().rotate(270);
    }else{
        Log::log("Gui station could not find rotation matrix to determine station image: inputdir" + to_string(inputDirection) + " outputdir: "+ to_string(outputDirection),Error);
    }
    l = new QLabel(this);
    l->setPixmap(QPixmap(imagePath.c_str()).scaled(MinStationSize,MinStationSize,Qt::KeepAspectRatio).transformed(rot));
    setMinimumSize(MinStationSize,MinStationSize);
    l->setScaledContents(true);

    Log::log("create station Info lable for"+ connectedStation->getStationName(),DebugL3);
    // PrintState Text
    stationState = new QLabel(this);
    stationState->setScaledContents(true);
    stationState->setText("station State gets updated on first Frame");
    stationState->adjustSize();
    stationState->show();

    // Display  Sensors
    Log::log("create station Sensors  ",DebugL3);
    guiSensors = new  vector<GuiSensor *>();
    vector<BaseSensor *> * sensors = connectedStation->getSensors();
    for(int i = 0; i<sensors->size();i++){
        GuiSensor *sen = new GuiSensor(sensors->at(i), connectedStation, this );
        guiSensors->push_back(sen);

    }
    // Display actuators
    Log::log("create station Actuator",DebugL3);
    vector<BaseActuator *> * actuators = connectedStation->getActuators();
    guiActuators = new vector<GuiActuator*>();
    for(int i = 0; i<actuators->size();i++){
        GuiActuator *guiActuator = new GuiActuator(actuators->at(i),connectedStation,this);
        guiActuator->raise();
        guiActuators->push_back(guiActuator);
    }
    Log::log("created all actuators",Info);
    // Change actuator State Button
    stationActuator = new QPushButton(this);
    stationActuator->setText("set Actuator State ");
    stationActuator->raise();
    stationActuator->move(this->size().width()-stationActuator->size().width(), 1);
    stationActuator->show();
    connect(stationActuator, SIGNAL(clicked()), this, SLOT(updateActuatorState()));


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
        // move box
        gb->moveToNewPos(pos(),width(),height(), connectedStation);
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
        stationStateText += sensors->at(i)->getSensorName() + " :" +  to_string(sensors->at(i)->getSensorState()) +"\r\n";
    }
    Log::log("current station state: " + stationStateText, DebugL3)
    stationState->setText(stationStateText.c_str());
    stationState->adjustSize();
    stationState->show();
    show();

    // update senspos
    for(int i = 0; i<guiSensors->size();i++){
        guiSensors->at(i)->update();
    }
    // update actuators
    for(int i = 0; i<guiActuators->size();i++){
        guiActuators->at(i)->update();
    }



}

void GuiStation::updateActuatorState() {
    Log::log("gui change actuator state for "+connectedStation->getStationName(),Info);
    connectedStation->getActuators()->at(0)->toogleState();
    stationActuator->raise();

}

void GuiStation::setWidetSize(uint32_t widgetSizeX_, uint32_t widgetSizeY_){
    widgetSizeX = widgetSizeX_;
    widgetSizeY = widgetSizeY_;
    l->setPixmap(QPixmap(imagePath.c_str()).scaled(widgetSizeX,widgetSizeY,Qt::KeepAspectRatio));

}
