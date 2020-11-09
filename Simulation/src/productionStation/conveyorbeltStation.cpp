//
// Created by basti on 09.11.2020.
//

#include <src/actuators/conveyorbelt.h>
#include "conveyorbeltStation.h"

void conveyorbeltStation::runSimulationStep() {
    //TODO
    conv->runActuator(boxSet,this);

}

conveyorbeltStation::conveyorbeltStation(BaseProductionStation *next, string name) :BaseProductionStation(next,"conveyorbeltStation:"+name ){
    conv = new conveyorbelt("Band1");
    addActuator(conv);
}

void conveyorbeltStation::setConveyorbeltState(actuatorState toSet) {
    conv->setActuatorState(toSet);
}
