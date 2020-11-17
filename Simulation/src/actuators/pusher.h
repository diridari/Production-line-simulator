//
// Created by basti on 17.11.2020.
//

#ifndef PRODUCTION_LINE_SIMULATOR_PUSHER_H
#define PRODUCTION_LINE_SIMULATOR_PUSHER_H


#include "BaseActuator.h"

class pusher: public BaseActuator {
    uint8_t pusherPosition;
public:
    pusher(string name,bool moveForward = true);
    void runActuator( vector<BaseWorkpiece*> * boxSet, BaseProductionStation *station);
};


#endif //PRODUCTION_LINE_SIMULATOR_PUSHER_H
