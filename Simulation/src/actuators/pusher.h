//
// Created by basti on 17.11.2020.
//

#ifndef PRODUCTION_LINE_SIMULATOR_PUSHER_H
#define PRODUCTION_LINE_SIMULATOR_PUSHER_H


#include "BaseActuator.h"

enum PushDirection{
    Idle,Forward,Backward
};

class pusher: public BaseActuator {
    int32_t pusherPosition;
    PushDirection direction = PushDirection::Idle;
public:
    pusher(string name = "pusher");
    void runActuator( vector<BaseWorkpiece*> * boxSet, BaseProductionStation *station);
    void setDirection(PushDirection direction);

};


#endif //PRODUCTION_LINE_SIMULATOR_PUSHER_H
