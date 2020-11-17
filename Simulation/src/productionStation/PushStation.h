//
// Created by basti on 17.11.2020.
//

#ifndef PRODUCTION_LINE_SIMULATOR_PUSHSTATION_H
#define PRODUCTION_LINE_SIMULATOR_PUSHSTATION_H


#include "BaseProductionStation.h"

class PushStation: public BaseProductionStation {

public:
    PushStation(BaseProductionStation * next, string name = "");
    void runSimulationStep();
};


#endif //PRODUCTION_LINE_SIMULATOR_PUSHSTATION_H
