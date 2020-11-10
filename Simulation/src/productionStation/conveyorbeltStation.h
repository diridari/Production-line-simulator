//
// Created by basti on 09.11.2020.
//

#ifndef PRODUCTION_LINE_SIMULATOR_CONVEYORBELTSTATION_H
#define PRODUCTION_LINE_SIMULATOR_CONVEYORBELTSTATION_H


#include <src/sensors/lightBarrier.h>
#include "BaseProductionStation.h"
#include "../actuators/conveyorbelt.h"

class conveyorbeltStation: public BaseProductionStation {
    conveyorbelt *conv;
    lightBarrier *lb;
public:
    conveyorbeltStation(BaseProductionStation * next, string name = "");
    void runSimulationStep();
    void setConveyorbeltState(actuatorState toSet);
};


#endif //PRODUCTION_LINE_SIMULATOR_CONVEYORBELTSTATION_H
