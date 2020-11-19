//
// Created by basti on 09.11.2020.
//

#include "conveyorbelt.h"
#include <src/workpiece/Placing.h>

conveyorbelt::conveyorbelt(string name) : BaseActuator("conveyorbelt:"+ name){
    kindOfAktuator = actuatorKind::Conveyorbelt_;
    actuatorImageActiv = "../img/convorbelt.png";
    actuatorImageInactiv = "../img/convorbeltInactiv.png";

    position = 50;
}

void conveyorbelt::runActuator(vector<BaseWorkpiece *> *boxSet, BaseProductionStation *station) {
    if(getActuatorState() == ACTUATOR_ON){
        Log::log("run conveyorbelt: move boxes on "+ getActuatorName() ,Debug)
        // move each box
        for(int i = boxSet->size()-1; i>= 0; i--){
            BaseWorkpiece * wp = boxSet->at(i);
            if(Placing::canWorkpieceBePlacedAt(station, wp, wp->getPosition() + 2)){

                if(wp->getPosition()+2 < BaseProductionStation::sizeOfStation) { // Move Box
                   wp->moveBy(2);
                }else{ // moved out of station
                    if(Placing::canStationReceiveNewWorkpiece(station->getNextStationInChain(),wp->getWorkpieceSize())) {
                        Log::log(station->getStationName() + ": element has moved out of Station --> move to next",
                                 Info);
                        boxSet->erase(boxSet->begin() + i); // drop element
                        station->getNextStationInChain()->insertBox(wp); // insert in next chain
                    }
                }
            }
        }
    }


}


