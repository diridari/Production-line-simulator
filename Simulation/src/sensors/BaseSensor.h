//
// Created by basti on 03.11.2020.
//

#ifndef PRODUCTION_LINE_SIMULATOR_BASESENSOR_H
#define PRODUCTION_LINE_SIMULATOR_BASESENSOR_H

#include <stdint.h>
#include <iostream>
using namespace std;

typedef enum sensorState{
    SENSOR_OFF, // no sensor Signal
    SENSOR_ON  // sensor Signal

} sensorState;
std::ostream &operator<<(ostream &strm, sensorState a);

class BaseSensor {
private:
    sensorState sensorState = SENSOR_OFF;
public:
    uint8_t getSensorState();
    friend std::ostream &operator<<(std::ostream &strm, BaseSensor a);

};


#endif //PRODUCTION_LINE_SIMULATOR_BASESENSOR_H
