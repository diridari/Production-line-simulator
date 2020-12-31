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
    int port;
public:
    /**
     * init the api interface
     * This creates a thread that listen on the port and response to  requests
     * @param port
     */
    api(BaseProductionStation * startStation,int port_ = 5555);
    /**
     * handle a single api request and generate a respond string
     * @param request  api reqeust string
     * @return respond string
     */
    string handleRequest(string request);
    BaseProductionStation * getStationByName(string stationName);
    string getNextToken(string * stringToAnalyze);
    int getPort(){
        return port;
    }

};


#endif //PRODUCTION_LINE_SIMULATOR_API_H
