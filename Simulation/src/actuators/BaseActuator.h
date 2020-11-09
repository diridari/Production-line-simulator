//
// Created by basti on 03.11.2020.
//

#ifndef PRODUCTION_LINE_SIMULATOR_BASEACTUATOR_H
#define PRODUCTION_LINE_SIMULATOR_BASEACTUATOR_H
#include <stdint.h>

class BaseActuator {
private:
    uint8_t actuatorState;
public:
    uint8_t getActuatorState();
};


#endif //PRODUCTION_LINE_SIMULATOR_BASEACTUATOR_H
