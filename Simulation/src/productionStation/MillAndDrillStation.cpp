//
// Created by basti on 23.11.2020.
//

#include <src/actuators/MillAndDriller.h>
#include "MillAndDrillStation.h"

void MillAndDrillStation::runSimulationStep() {
    if(nextStation != nullptr){
        nextStation->runSimulationStep();
    }
    Log::log("run sim step for conveyorbeltStation:"+stationName ,DebugL2)
    conv->runActuator(boxSet,this);
    checkAllSensors();
}

void MillAndDrillStation::setConveyorbeltState(actuatorState toSet) {
    conv->setActuatorState(toSet);
}

MillAndDrillStation::MillAndDrillStation(BaseProductionStation *next, string name):BaseProductionStation(next,name) {
    conv = new conveyorbelt("Band");
    lb = new lightBarrier(50);
    addActuator(conv);
    addActuator(new MillAndDriller("driller"));
    addSensor(lb);
}
