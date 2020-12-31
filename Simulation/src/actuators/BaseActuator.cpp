//
// Created by basti on 03.11.2020.
//

#include "BaseActuator.h"

actuatorState BaseActuator::getActuatorState() {
    return actuatorState_;
}

string BaseActuator::getActuatorName() {
    return actuatorName;
}

std::ostream &operator<<(ostream &strm, BaseActuator &a) {
    strm << "" << a.getActuatorName() << " : {state:"  << a.getActuatorState() <<"}" ;
    return strm;
}

void BaseActuator::setActuatorState(actuatorState toSet) {
    actuatorState_ = toSet;
}

void BaseActuator::toogleState() {
    if(actuatorState_ == ACTUATOR_ON){
        actuatorState_ =ACTUATOR_OFF;
    }else{
        actuatorState_ = ACTUATOR_ON;
    }

}

actuatorKind BaseActuator::getActuatorKind() {
    return kindOfAktuator;
}

string BaseActuator::getActuatorImage() {
    if(actuatorState_ == ACTUATOR_ON){
        return actuatorImageActiv;

    }else{
        return actuatorImageInactiv;

    }
}

int32_t BaseActuator::getPosition() {
    return position;
}

string BaseActuator::getActuatorInfo() {
    return ActuatorInfo + " \r\n \t\t    position: "  + to_string(position);
}


std::ostream &operator<<(ostream &strm, actuatorState a) {
    switch (a) {
        case ACTUATOR_OFF :
            strm << "ACTUATOR_OFF";
            break;
        case ACTUATOR_ON :
            strm << "ACTUATOR_ON";
            break;
    }
    return strm;
}
