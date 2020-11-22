//
// Created by basti on 03.11.2020.
//

#include "BaseSensor.h"




std::ostream &operator<<(ostream &strm, BaseSensor a) {
    strm << "BaseSensor : {state:"  << a.getSensorState() <<"}" ;
    return strm << " ";
}

string BaseSensor::getSensorName() {
    return sensorName;
}

BaseSensor::BaseSensor(uint32_t placedAt_ = 0, string sensorName_) : placedAt(placedAt_), sensorName(sensorName_){}

uint32_t BaseSensor::getSensorPos() {
    return placedAt;
}

sensorState BaseSensor::getSensorState() {
    return sensorState_;
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