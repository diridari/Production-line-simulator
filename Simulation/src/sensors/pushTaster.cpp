//
// Created by basti on 09.12.2020.
//

#include "pushTaster.h"

pushTaster::pushTaster(uint32_t placedAt,int32_t detect_, pusher *connectedPusher_,string name):BaseSensor(placedAt,name) {
    connectedPusher = connectedPusher_;
    kinfOfSensor = sensorKind::taster;
    sensOnImage = "../img/pushOn.png";
    sensOffImage = "../img/pushOff.png";
    detect = detect_;

    SensorInfo = "Pushtaster. when the Pusher on that station is near the sensors position this sensor sends a active signal";
}

void pushTaster::checkSensor(vector<BaseWorkpiece *> *boxSet) {
    int32_t sensRange_min,sensorRagen_max;
    int32_t tmp = placedAt + detect;
    if(tmp<placedAt){
        sensRange_min = tmp;
        sensorRagen_max = placedAt;
    }else{
            sensRange_min = placedAt;
            sensorRagen_max = tmp;
    }
    if(connectedPusher->getPosition() >= sensRange_min && connectedPusher->getPosition() <= sensorRagen_max) {
        sensorState_ = SENSOR_ON;
    }
    else {
        sensorState_ = SENSOR_OFF;
    }
}
