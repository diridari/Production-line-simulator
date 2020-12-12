//
// Created by basti on 17.11.2020.
//

#include <src/sensors/pushTaster.h>
#include "PushStation.h"

PushStation::PushStation(BaseProductionStation *next, string name):BaseProductionStation(next,name) {
    pusher_ = new pusher(name);
    addActuator(pusher_);
    addSensor(new pushTaster(4,-10,pusher_,"pushTasterFront"));
    addSensor(new pushTaster(90,10,pusher_,"pushTasterBack"));
}

void PushStation::runSimulationStep() {
    BaseProductionStation::runSimulationStep();
    pusher_->runActuator(boxSet,this);
   for(int i = 0; i<sensorSet->size();i++){
       sensorSet->at(i)->checkSensor(boxSet); // box set not needed by pusher but required
   }

}

bool PushStation::stationCanReceiveNewBoxes() {

    return pusher_->getPosition()<= 5 && boxSet->size() == 0;
}
