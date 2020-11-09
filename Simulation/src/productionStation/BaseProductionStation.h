//
// Created by basti on 06.11.2020.
//

#ifndef PRODUCTION_LINE_SIMULATOR_BASEPRODUCTIONSTATION_H
#define PRODUCTION_LINE_SIMULATOR_BASEPRODUCTIONSTATION_H

#include <string>
#include <queue>
#include <src/workpiece/BaseWorkpiece.h>
#include <src/sensors/BaseSensor.h>
#include <src/actuators/BaseActuator.h>

using namespace std;
class BaseProductionStation {


protected:
    BaseProductionStation *nextStation = nullptr;
    string stationName;
    std::queue<BaseWorkpiece*> * boxSet;
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

    void runSimulationStep();
    bool canReceiveNewWorkpiece();

   friend std::ostream &operator<<(std::ostream &strm, BaseProductionStation a);


};

#endif //PRODUCTION_LINE_SIMULATOR_BASEPRODUCTIONSTATION_H
