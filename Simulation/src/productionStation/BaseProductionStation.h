//
// Created by basti on 06.11.2020.
//

#ifndef PRODUCTION_LINE_SIMULATOR_BASEPRODUCTIONSTATION_H
#define PRODUCTION_LINE_SIMULATOR_BASEPRODUCTIONSTATION_H

#include <string>
#include <queue>
#include <lib/SimpleLogging/include/logging.h>
#include <src/actuators/BaseActuator.h>
#include "../sensors/BaseSensor.h"
using namespace std;

typedef enum Direction{
    directionUp,directionDown,directionLeft,directionRight
}Direction;
class BaseActuator;
class BaseProductionStation {

protected:
    BaseProductionStation *nextStation = nullptr; // next station in Chain   nullpntr = last station
    string stationName; // name of this station
    vector<BaseWorkpiece*> * boxSet;
    vector<BaseSensor*> * sensorSet;
    vector<BaseActuator*> * actuatorSet;
    Direction inputDirection,outputDirection;

public:

    static const uint32_t sizeOfStation = 100;
    /**
     * New production station
     * @param nextStation next station in chain.nullpointer defines the end of the chain
     * @param stationName name of station
     * @param inputDirection  from where incoming boxes are received
     * @param outputDirection from where outgoing boxes are leaving
     */
    explicit BaseProductionStation(BaseProductionStation * nextStation = nullptr, string stationName = "namelessStation",
                                   Direction inputDirection = directionLeft,Direction outputDirection = directionRight);
    string getStationName();

    void setOutputDirection(Direction outputDirection_);
    void setInputDirection(Direction inputDirection_);
    void setDirection(Direction inputDirection_,Direction outputDirection_);
    /**
     * add a Sensor to that station
     * needed for defining the station
     * @param toAadd sensor to add
     */
    void addSensor(BaseSensor * toAadd);
    /**
     * add a Actuator to that station
     * needed for defining the station
     * @param toAadd actuator to add
     */
    void addActuator(BaseActuator * toAadd);


    /**
     * insert box at the begin of the station
     * Just possible if there is space check canReceiveNewWorkpiece
     * @param wp
     * @return true on success
     */
    bool insertBox(BaseWorkpiece *wp, uint32_t posToInsert = 0);

    /**
     * run one simulation step for this station:
     *      * 1. Operate all Workpieces on that station
     *      1.1 each station has a set of boxes that are on that stage
     *      1.2 a box get moved to the next station if
     *          a) the next station is movable
     *          b) there are no blocking elements
     *          then it is changing the current station
     *      1.3 a box can move inside the same station if
     *          a) the station is moving
     *          b) there is no blocking box on the left hand side
     *
     *      2. Depending of the new box positions the sensor states gets calculated
     *
     */
    virtual void runSimulationStep();

    /**
     * is the station able (independent from the boxes) to receive a new box (e.g. the pusher can not allways receive boxes)
     * @return true if station is capable to receive a new box
     */
    virtual bool stationCanReceiveNewBoxes();
    vector<BaseWorkpiece*> *getBoxesOnStation();
    vector<BaseSensor*> * getSensors();
    vector<BaseActuator*> * getActuators();
    BaseProductionStation * getNextStationInChain();
    Direction getInputDirection();
    Direction getOutputDirection();
    friend std::ostream &operator<<(std::ostream &strm, BaseProductionStation a);
    void checkAllSensors();


};

#endif //PRODUCTION_LINE_SIMULATOR_BASEPRODUCTIONSTATION_H
