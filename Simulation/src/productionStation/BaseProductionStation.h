//
// Created by basti on 06.11.2020.
//

#ifndef PRODUCTION_LINE_SIMULATOR_BASEPRODUCTIONSTATION_H
#define PRODUCTION_LINE_SIMULATOR_BASEPRODUCTIONSTATION_H

#include <string>
#include <queue>
#include <lib/SimpleLogging/include/logging.h>
#include <src/workpiece/BaseWorkpiece.h>
#include <src/actuators/BaseActuator.h>
#include <src/sensors/BaseSensor.h>


using namespace std;
class BaseWorkpiece; // beak circular dependencies
class BaseActuator;

class BaseProductionStation {
    static uint32_t sizeOfStation = 100;

protected:
    BaseProductionStation *nextStation = nullptr;
    string stationName;
    vector<BaseWorkpiece*> * boxSet;
    vector<BaseSensor*> * sensorSet;
    vector<BaseActuator*> * actuatorSet;

public:
    /**
     * New production station
     * @param nextStation next station in chain.nullpointer defines the end of the chain
     * @param stationName name of station
     */
    explicit BaseProductionStation(BaseProductionStation * nextStation = nullptr, string stationName = "namelessStation");
    string getStationName();
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
    bool insertBox(BaseWorkpiece *wp);
    virtual void runSimulationStep();
    bool canReceiveNewWorkpiece(uint8_t sizeOfBox = 1);
    bool canWorkpieceBePlacedAt(uint8_t posToPlace,BaseWorkpiece *toPlace);

   friend std::ostream &operator<<(std::ostream &strm, BaseProductionStation a);


};

#endif //PRODUCTION_LINE_SIMULATOR_BASEPRODUCTIONSTATION_H
