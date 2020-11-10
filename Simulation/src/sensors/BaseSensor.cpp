//
// Created by basti on 03.11.2020.
//

#include "BaseSensor.h"

uint8_t BaseSensor::getSensorState() {
    return sensorState;
}


std::ostream &operator<<(ostream &strm, BaseSensor a) {
    strm << "BaseSensor : {state:"  << a.getSensorState() <<"}" ;
    return strm << " ";
}

std::ostream &operator<<(ostream &strm, sensorState a) {
    switch (a) {
        case SENSOR_OFF :
            strm << "SENSOR_OFF";
            break;
        case SENSOR_ON :
            strm << "SENSOR_ON";
            break;
    }
    return strm;
}
