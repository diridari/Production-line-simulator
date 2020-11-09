//
// Created by basti on 09.11.2020.
//

#ifndef PRODUCTION_LINE_SIMULATOR_CONVEYORBELT_H
#define PRODUCTION_LINE_SIMULATOR_CONVEYORBELT_H


#include "BaseActuator.h"

class conveyorbelt: public BaseActuator {

public:
    conveyorbelt(string name);
    void runActuator( vector<BaseWorkpiece*> * boxSet, BaseProductionStation *nextStation);

};


#endif //PRODUCTION_LINE_SIMULATOR_CONVEYORBELT_H
