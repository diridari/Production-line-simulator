//
// Created by basti on 12.12.2020.
//

#include "api.h"
#if selfTest != 1
#include <zmq.h>
#endif
#include <cassert>
#include <thread>
#include <unistd.h>

/*
 * c conveyorbeltStation(nullptr,"End");
PushStation *c5 = new PushStation(c6,"Push 2");
MillAndDrillStation *c4 = new MillAndDrillStation(c5,"Drill");
MillAndDrillStation *c3 = new MillAndDrillStation(c4,"Mill");
PushStation *c2 = new PushStation(c3,"Push1");
conveyorbeltStation *c1 = new conveyorbeltStation(c2,"Start");
 */
void workerThread(void * responder, api* api){
    Log::log("started api worker thread",Info);

    while(1){
#if selfTest != 1
        Log::log("api wait for new data",Info);
        char buffer [67];
        int rc = zmq_recv (responder, buffer, 10, 0);
        Log::log("api send respond",Info);
        zmq_send(responder,"ok",2,0);

        printf ("Received %s\n",buffer);
#endif
        usleep(1);
    }
}

api::api(BaseProductionStation *startStation_, int port) {
    Log::log("init api",Info);
    startStation = startStation_;
#if selfTest != 1

    void *context = zmq_ctx_new ();
    responder = zmq_socket (context, ZMQ_REP);
    int rc = zmq_bind (responder, "tcp://*:5555");
    assert (rc == 0);
    new thread(workerThread,responder,this);
#endif
}


BaseProductionStation *api::getStationByName(string stationName) {
    Log::log("api: get station by name",DebugL2);
    BaseProductionStation *station = startStation;
    while (station != nullptr){
        if(station->getStationName() == stationName)
            return station;
        station = station->getNextStationInChain();
    }
    Log::log("api: get station by name: no such station: "+ stationName,Message);

    return nullptr;
}

string api::getNextToken(string *stringTo) {
    Log::log("api: get next string token",DebugL2);
    if(stringTo == nullptr || *stringTo == ""){
        Log::log("api: failed to get next token  ",Error);
        return "";
    }
    int tokenEndIndex = stringTo->find(' ');
    string outstring;
    if(tokenEndIndex != string::npos){ // end of string
        outstring = stringTo->substr(0,tokenEndIndex);
        *stringTo = stringTo->substr(tokenEndIndex+1,stringTo->size()-1);
    }else{
        outstring = *stringTo;
        *stringTo = "";
    }
    if(outstring.empty() || outstring == " ")
        return getNextToken(stringTo); // If multiple spaces
    return outstring;
}

string api::handleRequest(string request) {
    string requestTmp = request;
    string out = "parsing error";
    string reqeustKind = getNextToken(&request);
    string stationName = getNextToken(&request);
    BaseProductionStation *station = getStationByName(stationName);
    string accessTo = getNextToken(&request);
    int accessID = stoi(accessTo);
    if(reqeustKind.empty()|| stationName.empty() || accessTo.empty() || (reqeustKind!="get" && reqeustKind != "set")){
        Log::log("invalic request:"+ requestTmp+"\t allowed requests are: [get/set] StationName ID [opt. Value]",Error);
        return "failed to pares request";
    }
    if(reqeustKind == "get"){
        if(station->getSensors()->at(accessID) == nullptr){
            Log::log("api access to not existing sensor \t request: "+requestTmp,Error);
            return "no such sensor";
        }
        out = "ok: " + to_string(station->getSensors()->at(accessID)->getSensorState());

    }else if(reqeustKind == "set"){

        if(station->getActuators()->at(accessID) == nullptr){
            Log::log("api access to not existing actuator \t request: "+requestTmp,Error);
            return "no such actuator";
        }
        string value = getNextToken(&request);
        if(value.empty()){
            Log::log("got get request but no value",Error);
            return "got no actuator value";
        }
        switch (stoi(value)) {
            case 0:         station->getActuators()->at(accessID)->setActuatorState(ACTUATOR_OFF); break;
            case 1:         station->getActuators()->at(accessID)->setActuatorState(ACTUATOR_ON); break;
            default: return "failed to set actuator to value";
        }
        out = "ok";

    }
    return out;
}



