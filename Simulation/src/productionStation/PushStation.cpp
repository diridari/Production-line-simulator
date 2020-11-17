//
// Created by basti on 17.11.2020.
//

#include "PushStation.h"

PushStation::PushStation(BaseProductionStation *next, string name):BaseProductionStation(next,"pusher:"+name) {
    pusher_ = new pusher(name);
}

void PushStation::runSimulationStep() {
    BaseProductionStation::runSimulationStep();

}

bool PushStation::stationCanReceiveNewBoxes() {
    return pusher_->getPosition()<= 0;
}
