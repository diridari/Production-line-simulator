//
// Created by basti on 03.11.2020.
//

#ifndef PRODUCTION_LINE_SIMULATOR_BASEACTUATOR_H
#define PRODUCTION_LINE_SIMULATOR_BASEACTUATOR_H
#include <stdint.h>
#include <string>
#include <iostream>
#include <lib/SimpleLogging/include/logging.h>
#include <src/workpiece/BaseWorkpiece.h>
#include <vector>
#include <src/productionStation/BaseProductionStation.h>

using namespace std;


enum actuatorState{
    ACTUATOR_OFF,
    ACTUATOR_ON
};

enum actuatorKind{
    BaseActuator_,
    Conveyorbelt_,
    Pusher,
    Miller,
    Driller
};
std::ostream &operator<<(std::ostream &strm, actuatorState a);
class BaseProductionStation;
class BaseActuator {
private:
    string  actuatorName;
    actuatorState actuatorState_ = ACTUATOR_OFF;

protected:
    int32_t position;
    actuatorKind kindOfAktuator = actuatorKind::BaseActuator_;

    string  actuatorImage = "";
public:
    int32_t getPosition();
    string getActuatorImage();
    actuatorKind getActuatorKind();
    BaseActuator(string name): actuatorName(name){};
    string getActuatorName();
    actuatorState getActuatorState();
    void setActuatorState(actuatorState toSet);

    /**
     * run this actuator for each Workpiece.
     * Workpieces can move to the next station if they reach the end of the station
     * @param boxSet set of boxes to run
     * @param nextStation
     */
    virtual void runActuator( vector<BaseWorkpiece*> * boxSet, BaseProductionStation *station) {};
    friend std::ostream &operator<<(std::ostream &strm, BaseActuator &a);
    void toogleState();
};


#endif //PRODUCTION_LINE_SIMULATOR_BASEACTUATOR_H
