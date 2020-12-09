//
// Created by basti on 09.12.2020.
//

#ifndef PRODUCTION_LINE_SIMULATOR_PUSHTASTER_H
#define PRODUCTION_LINE_SIMULATOR_PUSHTASTER_H


#include <src/actuators/pusher.h>
#include "BaseSensor.h"
#define PUSHTASTER_OFFSET 10
class pushTaster: public BaseSensor {

    pusher *connectedPusher;
    int32_t detect;
public:
    pushTaster(uint32_t placedAt,int32_t detect,pusher *connectedPusher1,string name);
    /**
    * run this actuator .
     * instead of checking the boxes the conected sensor gets checked
    * @param boxSet set of boxes to run
    * @param nextStation
    */
    void checkSensor( vector<BaseWorkpiece*> * boxSet);
};


#endif //PRODUCTION_LINE_SIMULATOR_PUSHTASTER_H
