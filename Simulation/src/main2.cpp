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
    void *sub = zmq_socket (context, ZMQ_SUB);
    zmq_connect (sub, "tcp://localhost:5556");
    //  Subscribe to the 'status' topic
    zmq_setsockopt (sub, ZMQ_SUBSCRIBE, "error", strlen ("error"));
    zmq_setsockopt (sub, ZMQ_SUBSCRIBE, "status", strlen ("status"));

    int request_nbr;
   while(1){
       char buff[64];
        int index = zmq_recv(sub,buff,64,0);
        int64_t  t;
        size_t more_size = sizeof t;
        zmq_getsockopt (sub,ZMQ_RCVMORE, &t, &more_size);
        while(t){
            index += zmq_recv(sub,buff+index-1,64-index,0);
            zmq_getsockopt (sub,ZMQ_RCVMORE, &t, &more_size);

        }
        std::cout << "got " << buff <<std::endl;
   }
    zmq_close (sub);
    zmq_ctx_destroy (context);
    return 0;
}