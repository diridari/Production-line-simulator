//
// Created by basti on 03.11.2020.
//

#ifndef PRODUCTION_LINE_SIMULATOR_BASEACTUATOR_H
#define PRODUCTION_LINE_SIMULATOR_BASEACTUATOR_H
#include <stdint.h>
#include <string>
#include <iostream>
#include <lib/SimpleLogging/include/logging.h>
#include <src/productionStation/BaseProductionStation.h>
#include <src/workpiece/BaseWorkpiece.h>

using namespace std;

class BaseProductionStation;
class BaseWorkpiece;
enum actuatorState{
    ACTUATOR_OFF,
    ACTUATOR_ON

};
std::ostream &operator<<(std::ostream &strm, actuatorState a);

class BaseActuator {
private:
    string  actuatorName;
    actuatorState actuatorState_ = ACTUATOR_OFF;
public:
    BaseActuator(string name): actuatorName(name){};
    string getActuatorName();
    actuatorState getActuatorState();
    void setActuatorState(actuatorState toSet);

    /**
     * run this actuator for each Workpiece.
     * Workpieces can move to the next station if thex reach the end of the station
     * @param boxSet set of boxes to run
     * @param nextStation
     */
    virtual void runActuator( vector<BaseWorkpiece*> * boxSet, BaseProductionStation *station) {};
    friend std::ostream &operator<<(std::ostream &strm, BaseActuator &a);
    void toogleState();
};


#endif //PRODUCTION_LINE_SIMULATOR_BASEACTUATOR_H
