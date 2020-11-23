//
// Created by basti on 23.11.2020.
//

#ifndef PRODUCTION_LINE_SIMULATOR_MILLANDDRILLSTATION_H
#define PRODUCTION_LINE_SIMULATOR_MILLANDDRILLSTATION_H


#include <src/sensors/lightBarrier.h>
#include <src/actuators/conveyorbelt.h>
#include <src/actuators/MillAndDriller.h>
#include "BaseProductionStation.h"

class MillAndDrillStation: public BaseProductionStation {
    conveyorbelt *conv;
    lightBarrier *lb;
public:
    MillAndDrillStation(BaseProductionStation * next, string name = "");

    void runSimulationStep();
    void setConveyorbeltState(actuatorState toSet);
};


#endif //PRODUCTION_LINE_SIMULATOR_MILLANDDRILLSTATION_H
