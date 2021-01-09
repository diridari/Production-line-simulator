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
    bool couldPlaceAllBoxes = true;
    if(newPos <= 95 && newPos >= 0 ) {

        // process all boxes if moving forward
        if (direction == PushDirection::Forward){
            Log::log("set pusher to position: " + to_string(position), DebugL3);

            for (int i = boxSet->size() - 1; i >= 0; i--) {
                BaseWorkpiece *wp = boxSet->at(i);
                if(wp->getPosition()<= newPos+wp->getWorkpieceSize()/2){
                     if (Placing::canWorkpieceBePlacedAt(station, wp, newPos+wp->getWorkpieceSize()/2)) {
                        if (newPos + wp->getWorkpieceSize() / 2 < BaseProductionStation::sizeOfStation) { // Move Box
                            wp->setPosition(newPos + wp->getWorkpieceSize() / 2);
                        } else { // moved out of station
                            Log::log(station->getStationName() + ": element has moved out of Station --> move to next",
                                     Info);
                            boxSet->erase(boxSet->begin() + i); // drop element
                            wp->setPosition(0); //reset pos information
                            station->getNextStationInChain()->insertBox(wp); // insert in next chain
                        }
                     }
                     else {
                        Log::log("can not place box on shifter at pos: " + to_string(newPos) + ""
                                     " the reason is that there is already a box. It is not allowed to move several boxes on the pusher at the same time!",
                                 Error);
                        couldPlaceAllBoxes = false;
                    }
                }
            }
        }
        if(couldPlaceAllBoxes){
            position = newPos; // increase the pusheractuator just if all boxes could be placed
        }
    }
    Log::log(" pusher pos: "+to_string(position),DebugL3);
}

void pusher::setDirection(PushDirection direction_) {
    Log::log("set pusher state to "+to_string(direction_),Debug);

    direction = direction_;
    if(direction_ != PushDirection::Idle){
        setActuatorState(actuatorState::ACTUATOR_ON);
    }
    else
        setActuatorState(actuatorState::ACTUATOR_OFF);
    updateImage();

}

void pusher::toogleState() {
    switch (direction) {
        case Idle:     setDirection(Forward); setActuatorState(actuatorState::ACTUATOR_ON);break;
        case Forward:  setDirection(Backward);  setActuatorState(actuatorState::ACTUATOR_ON);break;
        case Backward: setDirection(Idle); setActuatorState(actuatorState::ACTUATOR_OFF); break;
    }
    updateImage();

}

PushDirection pusher::getDirection() {
    return direction;
}

void pusher::updateImage() {
    switch (direction) {
        case Forward:     actuatorImageActiv = "../img/pusherForward.png"  ;break;
        case Backward:  actuatorImageActiv = "../img/pusherBackward.png";break;
        case Idle: break;
    }
}

