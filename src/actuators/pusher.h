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
    PushDirection direction = PushDirection::Idle;

public:
    pusher(string name = "pusher");
    void runActuator( vector<BaseWorkpiece*> * boxSet, BaseProductionStation *station);
    void setDirection(PushDirection direction);
    PushDirection getDirection();
    void toogleState();
    void updateImage();


};


#endif //PRODUCTION_LINE_SIMULATOR_PUSHER_H
