//
// Created by basti on 12.12.2020.
//

#ifndef PRODUCTION_LINE_SIMULATOR_API_H
#define PRODUCTION_LINE_SIMULATOR_API_H
#include <iostream>
#include <src/sensors/BaseSensor.h>
#include <src/actuators/BaseActuator.h>

using namespace std;


class api {
    BaseProductionStation * startStation;
    void *responder;

public:
    /**
     * init the api interface
     * This creates a thread that listen on the port and response to  requests
     * @param port
     */
    api(BaseProductionStation * startStation,int port = 5555);
    void handleRequest(string request);
    BaseProductionStation * getStationByName(string stationName);
    string getNextToken(string * stringToAnalyze);

};


#endif //PRODUCTION_LINE_SIMULATOR_API_H
