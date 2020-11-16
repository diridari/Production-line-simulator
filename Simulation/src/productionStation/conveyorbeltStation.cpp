//
// Created by basti on 09.11.2020.
//

#include <src/actuators/conveyorbelt.h>
#include "conveyorbeltStation.h"

void conveyorbeltStation::runSimulationStep() {
    if(nextStation != nullptr){
        nextStation->runSimulationStep();
    }
    Log::log("run sim step for conveyorbeltStation:"+stationName ,DebugL2)
    conv->runActuator(boxSet,this);
    checkAllSensors();

}

conveyorbeltStation::conveyorbeltStation(BaseProductionStation *next, string name) :BaseProductionStation(next,"conveyorbeltStation:"+name ){
    conv = new conveyorbelt("Band1");
    lb = new lightBarrier(80);
    addActuator(conv);
    addSensor(lb);
    addSensor(new lightBarrier(50));
}

void conveyorbeltStation::setConveyorbeltState(actuatorState toSet) {
    conv->setActuatorState(toSet);
}
