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
