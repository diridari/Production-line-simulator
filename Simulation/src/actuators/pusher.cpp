//
// Created by basti on 17.11.2020.
//

#include <src/workpiece/Placing.h>
#include "pusher.h"

pusher::pusher(string name) : BaseActuator("pusher:"+name) {
    position = 0;
    actuatorImageActiv = "../img/pusherForward.png";
    actuatorImageInactiv = "../img/pusherInactiv.png";
    kindOfAktuator = actuatorKind::Pusher;
}

void pusher::runActuator(vector<BaseWorkpiece *> *boxSet, BaseProductionStation *station) {
    int32_t newPos;
    switch (direction) {
        case PushDirection::Backward : newPos = position -2;    break;
        case PushDirection::Idle :  newPos = position;          break;
        case PushDirection::Forward :  newPos = position +2;    break;
    }
    if(newPos <= 100 && newPos >= 0 ) {
        position = newPos;
        // process all boxes if moving forward
        if (direction == PushDirection::Forward){
            Log::log("set pusher to position: " + to_string(position), DebugL3);

            for (int i = boxSet->size() - 1; i >= 0; i--) {
                BaseWorkpiece *wp = boxSet->at(i);
                if (Placing::canWorkpieceBePlacedAt(station, wp, newPos)) {
                    if (newPos < BaseProductionStation::sizeOfStation ) { // Move Box
                        if(wp->getPosition() < newPos)
                            wp->setPosition(newPos);
                    } else { // moved out of station
                        Log::log(station->getStationName() + ": element has moved out of Station --> move to next",
                                 Info);
                        boxSet->erase(boxSet->begin() + i); // drop element
                        wp->setPosition(0); //reset pos information
                        station->getNextStationInChain()->insertBox(wp); // insert in next chain
                    }
                } else {
                    Log::log("can not place box on shifter at pos: " + to_string(newPos) + ""
                                 " the reason is that there is already a box. It is not allowed to move several boxes on the pusher at the same time!",
                             Error);
                }
            }
        }
    }
    Log::log(" pusher pos: "+to_string(position),DebugL3);
}

void pusher::setDirection(PushDirection direction_) {
    Log::log("set pusher state to "+to_string(direction_),Info);
    direction = direction_;
}

void pusher::toogleState() {

    switch (direction) {
        case Idle:     setDirection(Forward); setActuatorState(actuatorState::ACTUATOR_ON); actuatorImageActiv = "../img/pusherForward.png"  ;break;
        case Forward:  setDirection(Backward);  setActuatorState(actuatorState::ACTUATOR_ON); actuatorImageActiv = "../img/pusherBackward.png";break;
        case Backward: setDirection(Idle); setActuatorState(actuatorState::ACTUATOR_OFF); break;
    }

}

