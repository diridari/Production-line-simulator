//
// Created by basti on 13.12.2020.
//

#ifndef PRODUCTION_LINE_SIMULATOR_DIRECTEDPUSHER_H
#define PRODUCTION_LINE_SIMULATOR_DIRECTEDPUSHER_H


#include "pusher.h"


/**
 * Two directed Pushers are connected to one undirected pusher. The reason is that a pusher has two input pins (forward
 * and backward) but the BaseActuator only can handle one input pin because a pusher exists out of two actuators
 */
class directedPusher: public BaseActuator {
    pusher * connectedPusher;
    PushDirection pushdirection;
public:
    explicit directedPusher (pusher * toHandle, PushDirection pushdirection);
    void runActuator( vector<BaseWorkpiece*> * boxSet, BaseProductionStation *station);

    int32_t getPosition(){
        return connectedPusher->getPosition();
    }
    string getActuatorImage(){
        return connectedPusher->getActuatorImage();
    }
    actuatorKind getActuatorKind();
    void toogleState();
    void setActuatorState(actuatorState toSet);

};


#endif //PRODUCTION_LINE_SIMULATOR_DIRECTEDPUSHER_H
