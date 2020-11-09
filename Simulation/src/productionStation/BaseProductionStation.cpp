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
    boxSet = new queue<BaseWorkpiece*>();
    sensorSet = new  vector<BaseSensor*>();
    actuatorSet = new vector<BaseActuator*>();
}

bool BaseProductionStation::canReceiveNewWorkpiece() {
    return true;
    //TODO
}

void BaseProductionStation::runSimulationStep() {
    // Move all Boxes
    
    // Check sensor State
}
