//
// Created by basti on 17.11.2020.
//

#include "PushStation.h"

PushStation::PushStation(BaseProductionStation *next, string name):BaseProductionStation(next,"pusher:"+name) {
    pusher_ = new pusher(name);
    addActuator(pusher_);
}

void PushStation::runSimulationStep() {
    BaseProductionStation::runSimulationStep();
    pusher_->runActuator(boxSet,this);

}

bool PushStation::stationCanReceiveNewBoxes() {

    return pusher_->getPosition()<= 5 && boxSet->size() == 0;
}
