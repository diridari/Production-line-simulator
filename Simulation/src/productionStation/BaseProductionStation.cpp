//
// Created by basti on 06.11.2020.
//

#include <lib/SimpleLogging/include/logging.h>
#include "BaseProductionStation.h"
#include <string>


std::ostream &operator<<(ostream &strm, BaseProductionStation a) {
    strm << "BaseProductionStation : {" << a.getStationName() <<"} ";

    return strm << " ";
}

void BaseProductionStation::addActuator(BaseActuator *toAadd) {
    Log::log("add new actuator to" + this->getStationName(),DebugL2);
    actuatorSet->push_back(toAadd);
}

void BaseProductionStation::addSensor(BaseSensor *toAadd) {
    Log::log("add new Sensor to" + this->getStationName(),DebugL2);
    sensorSet->push_back(toAadd);
}

string BaseProductionStation::getStationName() {
    return stationName;
}

BaseProductionStation::BaseProductionStation(BaseProductionStation *nextStation, string stationName,Direction inputDirection,Direction outputDirection) :
        nextStation(nextStation), stationName(stationName), outputDirection(outputDirection),inputDirection(inputDirection){
    boxSet = new vector<BaseWorkpiece*>();
    sensorSet = new  vector<BaseSensor*>();
    actuatorSet = new vector<BaseActuator*>();
}

bool BaseProductionStation::canReceiveNewWorkpiece(uint8_t sizeOfBox ) {

    // get left box
   for(int i = 0; i<boxSet->size();i++){ // has boxes
        BaseWorkpiece *box = boxSet->at(i);
        if(box->getPosition() <=  (sizeOfBox/2 + sizeOfBox%2)){
            return false;
        }
    }

    return true;
}


void BaseProductionStation::runSimulationStep() {
    if(nextStation != nullptr){
        nextStation->runSimulationStep();
    }
   // Log::log("run sim step for BaseProductionStation" + stationName,DebugL2)
}

bool BaseProductionStation::insertBox(BaseWorkpiece *wp) {
    Log::log("insertBox on station " + getStationName() + " boxName: "+wp->getName(),DebugL2);
    if(wp->canWorkpieceBePlacedAt(wp->getPosition(),this)){
        boxSet->insert(boxSet->begin(),wp);
        //boxSet->push_back(wp);
        return true;
    }
    Log::log(getStationName() + " should insert box but can not place new box",Error);
    return false;
}

vector<BaseWorkpiece *> *BaseProductionStation::getBoxesOnStation() {
    return boxSet;
}

vector<BaseActuator *> *BaseProductionStation::getActuators() {
    return actuatorSet;
}

vector<BaseSensor *> *BaseProductionStation::getSensors() {
    return sensorSet;
}

BaseProductionStation *BaseProductionStation::getNextStationInChain() {
    return nextStation;
}

Direction BaseProductionStation::getInputDirection() {
    return inputDirection;
}

Direction BaseProductionStation::getOutputDirection() {
    return outputDirection;
}

void BaseProductionStation::setDirection(Direction inputDirection_, Direction outputDirection_) {
    outputDirection = outputDirection_;
    inputDirection = inputDirection_;
}

void BaseProductionStation::setInputDirection(Direction inputDirection_) {
    inputDirection = inputDirection_;
}

void BaseProductionStation::setOutputDirection(Direction outputDirection_) {
    outputDirection = outputDirection_;
}

void BaseProductionStation::checkAllSensors() {
    for(int i = 0; i<sensorSet->size();i++){
        sensorSet->at(i)->checkSensor(boxSet);
    }

}

