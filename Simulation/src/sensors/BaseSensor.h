//
// Created by basti on 03.11.2020.
//

#ifndef PRODUCTION_LINE_SIMULATOR_BASESENSOR_H
#define PRODUCTION_LINE_SIMULATOR_BASESENSOR_H

#include <iostream>
#include <vector>
using namespace std;
class BaseWorkpiece;
enum sensorState{
    SENSOR_OFF, // no sensor Signal
    SENSOR_ON  // sensor Signal

};
std::ostream &operator<<(ostream &strm, sensorState a);

class BaseSensor {
protected:
    sensorState sensorState_ = SENSOR_OFF;
    string sensorName;
    uint32_t placedAt;

public:
    uint32_t getSensorPos();
    explicit BaseSensor(uint32_t placedAt, string sensorName = "baseSensor");
    string getSensorName();
    sensorState getSensorState();
    /**
    * run this actuator for each Workpiece.
    * Workpieces can move to the next station if thex reach the end of the station
    * @param boxSet set of boxes to run
    * @param nextStation
    */
    virtual void checkSensor( vector<BaseWorkpiece*> * boxSet) {};
    friend std::ostream &operator<<(std::ostream &strm, BaseSensor a);

};


#endif //PRODUCTION_LINE_SIMULATOR_BASESENSOR_H
