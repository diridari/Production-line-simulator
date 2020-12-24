//
// Created by basti on 09.11.2020.
//

#include "lightBarrier.h"
#include <lib/SimpleLogging/include/logging.h>

void lightBarrier::checkSensor(vector<BaseWorkpiece *> *boxSet) {
    if(boxSet == nullptr){
        Log:log("lightBarrier received nullptr",Error);
        return;
    }
    sensorState_ = SENSOR_OFF;
    for(int i = boxSet->size()-1; i>= 0; i--){
        BaseWorkpiece *wp = boxSet->at(i);
        uint8_t radius = (wp->getWorkpieceSize()/2 + wp->getWorkpieceSize()%2);
        int32_t box_min = wp->getPosition()-radius;
        int32_t box_max = wp->getPosition()+radius;

        if(box_min <= placedAt && box_max >= placedAt){
            sensorState_ = SENSOR_ON;
        }
    }

}

lightBarrier::lightBarrier(uint32_t placedAt):BaseSensor(placedAt,"lightBarrier") {
    kinfOfSensor = sensorKind::lightSensor;
    sensOnImage = "../img/lightSensDetect.png";
    sensOffImage = "../img/lightSensIdle.png";

    SensorInfo = "Light Barrier. When a box passes through the sensor, an active signal is sent by the sensor.";
}

