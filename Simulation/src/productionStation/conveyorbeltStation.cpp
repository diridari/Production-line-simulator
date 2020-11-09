//
// Created by basti on 09.11.2020.
//

#include <src/actuators/conveyorbelt.h>
#include "conveyorbeltStation.h"

void conveyorbeltStation::runSimulationStep() {
    if(conv->getActuatorState() == ACTUATOR_ON){
        Log::log("move boxes on "+ this->getStationName(),Debug)
        for(int i = boxSet->size()-1; i>= 0; i--){
            BaseWorkpiece * wp = boxSet->at(i);
            wp->moveBy(2);
        }
    }


}

conveyorbeltStation::conveyorbeltStation(BaseProductionStation *next, string name) :BaseProductionStation(next,"conveyorbeltStation:"+name ){
    conv = new conveyorbelt("Band1");
    addActuator(conv);
}

void conveyorbeltStation::setConveyorbeltState(actuatorState toSet) {
    conv->setActuatorState(toSet);
}
