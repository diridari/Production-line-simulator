//
// Created by basti on 23.11.2020.
//

#include "MillAndDriller.h"

MillAndDriller::MillAndDriller(string name) : BaseActuator("Driller:"+name) {
    kindOfAktuator = actuatorKind::MillerDrill;
    actuatorImageActiv = "../img/driller.png";
    actuatorImageInactiv = "../img/drillerInactiv.png";

    position = 50;

    ActuatorInfo = "Miller and Driller. This Actuator has no real effect";
}
