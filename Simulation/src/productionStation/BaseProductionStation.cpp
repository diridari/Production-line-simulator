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

BaseProductionStation::BaseProductionStation(BaseProductionStation *nextStation, string stationName) : nextStation(nextStation), stationName(stationName){
    boxSet = new vector<BaseWorkpiece*>();
    sensorSet = new  vector<BaseSensor*>();
    actuatorSet = new vector<BaseActuator*>();
}

bool BaseProductionStation::canReceiveNewWorkpiece(uint8_t sizeOfBox ) {

    // get left box
    if(boxSet->size() >0){ // has boxes
        BaseWorkpiece *box = boxSet->at(0);
        if(box->getPosition() <=  (sizeOfBox/2 + sizeOfBox%2)){
            return false;
        }
    }

    return true;
}
bool BaseProductionStation::canWorkpieceBePlacedAt(uint8_t posToPlace, BaseWorkpiece *toPlace) {

    if(boxSet->size() >0){ // has boxes
        uint8_t radius = (toPlace->getWorkpieceSize()/2 + toPlace->getWorkpieceSize()%2);
        int32_t box_min = toPlace->getPosition()-radius;
        int32_t box_max = toPlace->getPosition()+radius;
        for(int i = 0; i<boxSet->size();i++){ // check each box
            BaseWorkpiece *box = boxSet->at(i);
            uint8_t radius = (box->getWorkpieceSize()/2 + box->getWorkpieceSize()%2);
            int32_t tmp_min = box->getPosition()-radius;
            int32_t tmp_max = box->getPosition()+radius;
            if(box_min > tmp_max && box_max < tmp_min){
                return false;
            }
        }
    }

    return true;
}



void BaseProductionStation::runSimulationStep() {

}

bool BaseProductionStation::insertBox(BaseWorkpiece *wp) {
    if(canReceiveNewWorkpiece()){
        boxSet->insert(boxSet->begin(),wp);
        return true;
    }
    return false;
}

