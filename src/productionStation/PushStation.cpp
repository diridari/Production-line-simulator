//
// Created by basti on 17.11.2020.
//

#include <src/sensors/pushTaster.h>
#include <src/actuators/directedPusher.h>
#include "PushStation.h"

PushStation::PushStation(BaseProductionStation *next, string name):BaseProductionStation(next,name) {
    pusher_ = new pusher(name);
    forwardPusher = new directedPusher(pusher_,PushDirection::Forward);
    backwardPusher = new directedPusher(pusher_,PushDirection::Backward);

    addActuator(forwardPusher);
    addActuator(backwardPusher);

    addSensor(new pushTaster(4,-10,pusher_,"pushTasterFront"));
    addSensor(new pushTaster(91,10,pusher_,"pushTasterBack"));
}

void PushStation::runSimulationStep() {
    BaseProductionStation::runSimulationStep();
    if(lastPushDirection){
        lastPushDirection = false;
        forwardPusher->runActuator(boxSet,this);
        backwardPusher->runActuator(boxSet,this);
    }else{
        lastPushDirection = true;
        backwardPusher->runActuator(boxSet,this);
        forwardPusher->runActuator(boxSet,this);
    }
    if( forwardPusher->getActuatorState() == actuatorState::ACTUATOR_OFF &&
            backwardPusher->getActuatorState() == actuatorState::ACTUATOR_OFF &&
            pusher_->getActuatorState() == actuatorState::ACTUATOR_ON) {
        pusher_->setDirection(PushDirection::Idle);
        pusher_->setActuatorState(actuatorState::ACTUATOR_OFF);
    }

    for(int i = 0; i<sensorSet->size();i++){
       sensorSet->at(i)->checkSensor(boxSet); // box set not needed by pusher but required
   }

}

bool PushStation::stationCanReceiveNewBoxes() {

    return pusher_->getPosition()<= 5 && boxSet->size() == 0;
}
