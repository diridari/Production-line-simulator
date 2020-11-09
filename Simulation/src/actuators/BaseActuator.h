//
// Created by basti on 03.11.2020.
//

#ifndef PRODUCTION_LINE_SIMULATOR_BASEACTUATOR_H
#define PRODUCTION_LINE_SIMULATOR_BASEACTUATOR_H
#include <stdint.h>
#include <string>
#include <iostream>
#include <lib/SimpleLogging/include/logging.h>

using namespace std;


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
    friend std::ostream &operator<<(std::ostream &strm, BaseActuator &a);
};


#endif //PRODUCTION_LINE_SIMULATOR_BASEACTUATOR_H
