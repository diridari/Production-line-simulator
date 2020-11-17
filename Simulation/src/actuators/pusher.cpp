//
// Created by basti on 17.11.2020.
//

#include "pusher.h"

pusher::pusher(string name,bool moveForward ) : BaseActuator("pusher:"+name) {
    pusherPosition = 0;
    if(moveForward)
        kindOfAktuator = actuatorKind::PusherFront;
    else
        kindOfAktuator = actuatorKind::PusherBack;
}

void pusher::runActuator(vector<BaseWorkpiece *> *boxSet, BaseProductionStation *station) {

}
