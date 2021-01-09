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

BaseSensor::BaseSensor(uint32_t placedAt_ = 0, string sensorName_) : placedAt(placedAt_), sensorName(sensorName_){
    sensOnImage = "../img/lightSensDetect.png";
    sensOffImage = "../img/lightSensIdle.png";

    SensorInfo = "a not further defined sensor";

}

uint32_t BaseSensor::getSensorPos() {
    return placedAt;
}

sensorState BaseSensor::getSensorState() {
    return sensorState_;
}

sensorKind BaseSensor::getSensorKind() {
    return kinfOfSensor;
}

string BaseSensor::getSensOffImage() {
    return sensOffImage;
}

string BaseSensor::getSensOnImage() {
    return sensOnImage;
}

string BaseSensor::getSensorInfo() {
    return SensorInfo+ " \r\n \t\t    position: "  + to_string(getSensorPos());
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
