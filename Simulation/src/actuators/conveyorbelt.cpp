//
// Created by basti on 09.11.2020.
//

#include "conveyorbelt.h"

conveyorbelt::conveyorbelt(string name) : BaseActuator("conveyorbelt:"+ name){}

void conveyorbelt::runActuator(vector<BaseWorkpiece *> *boxSet, BaseProductionStation *nextStation) {
    if(getActuatorState() == ACTUATOR_ON){
        Log::log("move boxes on "+ getActuatorName() ,Debug)
        // move each box
        for(int i = boxSet->size()-1; i>= 0; i--){
            BaseWorkpiece * wp = boxSet->at(i);
            if(canWorkpiece be placed at(box pos + toAdd)) // check also transition

        }
    }


}


