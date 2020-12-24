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
    MillerDrill,

};
std::ostream &operator<<(std::ostream &strm, actuatorState a);
class BaseProductionStation;
class BaseActuator {
private:
    string  actuatorName;
    actuatorState actuatorState_ = ACTUATOR_OFF;

protected:
    /**
     * the postion of the actuator
     * this value can change if the avtuator is moving
     */
    int32_t position = 0;
    actuatorKind kindOfAktuator = actuatorKind::BaseActuator_;

    string  actuatorImageActiv = "";
    string  actuatorImageInactiv = "";

public:
    virtual int32_t getPosition();
    virtual string getActuatorImage();
    virtual actuatorKind getActuatorKind();
    BaseActuator(string name): actuatorName(name){};
    virtual string getActuatorName();
    virtual actuatorState getActuatorState();
    virtual void setActuatorState(actuatorState toSet);

    /**
     * run this actuator for each Workpiece.
     * Workpieces can move to the next station if they reach the end of the station
     * @param boxSet set of boxes to run
     * @param nextStation
     */
    virtual void runActuator( vector<BaseWorkpiece*> * boxSet, BaseProductionStation *station) {};
    friend std::ostream &operator<<(std::ostream &strm, BaseActuator &a);
    virtual void toogleState();
};


#endif //PRODUCTION_LINE_SIMULATOR_BASEACTUATOR_H
