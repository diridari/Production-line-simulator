//
// Created by basti on 12.12.2020.
//

#include "api.h"
#if Test != 1
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
#if Test != 1
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
#if Test != 1

    void *context = zmq_ctx_new ();
    responder = zmq_socket (context, ZMQ_REP);
    int rc = zmq_bind (responder, "tcp://*:5555");
    assert (rc == 0);
    new thread(workerThread,responder,this);
#endif
}

void api::handleRequest(string request) {


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
int getIndexOf(string *s, char c){
    for(int i = 0; i<s->length();i++){
        if(s->at(i) == c)
            return i;
    }
    return -1;
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
        outstring = stringTo->substr(0,tokenEndIndex-1);
        *stringTo = stringTo->substr(tokenEndIndex+1,stringTo->size()-1);
    }else{
        outstring = *stringTo;
        *stringTo = "";
    }
    if(outstring.empty())
        return getNextToken(stringTo); // If multiple spaces
    return outstring;
}

