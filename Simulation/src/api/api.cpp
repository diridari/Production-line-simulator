//
// Created by basti on 12.12.2020.
//

#include "api.h"
#include <zmq.h>
#include <cassert>
#include <thread>

void workerThread(void * responder, api* api){
    Log::log("started api worker thread",Info);

    while(1){
        Log::log("api wait for new data",Info);
        char buffer [67];
        int rc = zmq_recv (responder, buffer, 10, 0);
        Log::log("api send respond",Info);
        zmq_send(responder,"ok",2,0);

        printf ("Received %s\n",buffer);
    }
}

api::api(BaseProductionStation *startStation_, int port) {
    Log::log("init api",Info);
    void *context = zmq_ctx_new ();
    responder = zmq_socket (context, ZMQ_REP);
    int rc = zmq_bind (responder, "tcp://*:5555");
    assert (rc == 0);
    new thread(workerThread,responder,this);
}

void api::handleRequest(string request) {

}

