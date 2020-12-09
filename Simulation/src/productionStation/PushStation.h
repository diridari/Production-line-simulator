//
// Created by basti on 17.11.2020.
//

#ifndef PRODUCTION_LINE_SIMULATOR_PUSHSTATION_H
#define PRODUCTION_LINE_SIMULATOR_PUSHSTATION_H


#include <src/actuators/pusher.h>
#include "BaseProductionStation.h"

class PushStation: public BaseProductionStation {
    pusher *pusher_;
public:
    PushStation(BaseProductionStation * next, string name = "");
    void runSimulationStep();
    /**
     * is the station able (independent from the boxes) to receive a new box (e.g. the pusher can not allways receive boxes)
     * @return
     */
    bool stationCanReceiveNewBoxes();

};


#endif //PRODUCTION_LINE_SIMULATOR_PUSHSTATION_H
