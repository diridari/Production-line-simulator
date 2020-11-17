//
// Created by basti on 09.11.2020.
//

#ifndef PRODUCTION_LINE_SIMULATOR_LIGHTBARRIER_H
#define PRODUCTION_LINE_SIMULATOR_LIGHTBARRIER_H


#include <src/workpiece/BaseWorkpiece.h>
#include "BaseSensor.h"
class lightBarrier: public BaseSensor {
public:
    lightBarrier(uint32_t placedAt);
    /**
    * run this actuator for each Workpiece.
    * Workpieces can move to the next station if thex reach the end of the station
    * @param boxSet set of boxes to run
    * @param nextStation
    */
    void checkSensor( vector<BaseWorkpiece*> * boxSet);;
};


#endif //PRODUCTION_LINE_SIMULATOR_LIGHTBARRIER_H
