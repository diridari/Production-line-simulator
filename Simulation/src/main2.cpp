//  Hello World client
#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
using namespace std;

void apiSend(string s, void * context ){
    printf("api send %s\r\n\t",s.c_str());
    char buff[64] = {0,};
    zmq_send (context, s.c_str(), s.size(), 0);
    memset(buff,0,64);
    zmq_recv (context, buff, 64, 0);
    printf ("Received %s\r\n", buff);
}
int main (void)
{
    printf ("Connecting to hello world server…\n");
    void *context = zmq_ctx_new ();
    void *requester = zmq_socket (context, ZMQ_REQ);
    zmq_connect (requester, "tcp://localhost:5555");

    int request_nbr;
    string s1 = "set Pusher1 0 1";
    string s2 = "set Pusher1 1 1";
    string s3 = "set Pusher1 0 0";
    string s4 = "set Pusher1 1 0";
    while(1){
        for(int i = 0; i<5;i++) {
            apiSend(s1, requester);
            usleep(500000);
            apiSend(s3, requester);
            usleep(500000);
        }
        apiSend(s1, requester);
        for(int i = 0; i<5;i++) {
            apiSend(s2, requester);
            usleep(500000);
            apiSend(s4, requester);
            usleep(500000);
        }
        apiSend(s3, requester);
        for(int i = 0; i<5;i++) {
            apiSend(s2, requester);
            usleep(500000);
            apiSend(s4, requester);
            usleep(500000);
        }

    }
    zmq_close (requester);
    zmq_ctx_destroy (context);
    return 0;
}