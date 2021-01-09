//
// Created by basti on 23.11.2020.
//

#include "BaseActuator.h"

#ifndef PRODUCTION_LINE_SIMULATOR_MILLANDDRILLSTATION_H
#define PRODUCTION_LINE_SIMULATOR_MILLANDDRILLER_H


class MillAndDriller: public BaseActuator {

public:
    MillAndDriller(string name);
    void runActuator( vector<BaseWorkpiece*> * boxSet, BaseProductionStation *station){};
};


#endif //PRODUCTION_LINE_SIMULATOR_MILLANDDRILLSTATION_H
