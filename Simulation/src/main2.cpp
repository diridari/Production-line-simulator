//  Hello World client
#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
using namespace std;

int main (void)
{
    printf ("Connecting to hello world server…\n");
    void *context = zmq_ctx_new ();
    void *requester = zmq_socket (context, ZMQ_REQ);
    zmq_connect (requester, "tcp://localhost:5555");

    int request_nbr;
    for (request_nbr = 0; request_nbr != 10; request_nbr++) {
        sleep(1);
        char buffer[64];
        int i = sprintf(buffer, "hello:%d",request_nbr);
        printf ("Sending%s …\n", buffer);
        zmq_send (requester, buffer, i, 0);
        memset(buffer,0,64);
        zmq_recv (requester, buffer, 10, 0);
        printf ("Received %s\n", buffer);
    }
    zmq_close (requester);
    zmq_ctx_destroy (context);
    return 0;
}