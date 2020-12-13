//
// Created by basti on 13.12.2020.
//

#include "directedPusher.h"



directedPusher::directedPusher(pusher *toHandle, PushDirection pushdirection_):BaseActuator("directedPusher") {
    connectedPusher = toHandle;
    pushdirection = pushdirection_;
}

void directedPusher::runActuator(vector<BaseWorkpiece *> *boxSet, BaseProductionStation *station) {

    if(getActuatorState() == actuatorState::ACTUATOR_ON){
        connectedPusher->setDirection(pushdirection);
        connectedPusher->runActuator(boxSet,station);
        connectedPusher->updateImage();
    }

}

void directedPusher::setActuatorState(actuatorState toSet) {
    BaseActuator::setActuatorState(toSet);
    connectedPusher->setActuatorState(toSet);
    if(toSet == actuatorState::ACTUATOR_ON){
        connectedPusher->setDirection(pushdirection);
    }else if(connectedPusher->getDirection() == pushdirection){
        connectedPusher->setDirection(PushDirection::Idle);
    }
}

actuatorKind directedPusher::getActuatorKind() {
    return connectedPusher->getActuatorKind();
}

void directedPusher::toogleState() {
    BaseActuator::toogleState();
    connectedPusher->toogleState();

}
