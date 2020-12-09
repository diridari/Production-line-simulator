//  Hello World server
#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <iostream>

using namespace  std;
int main (void)
{
    //  Socket to talk to clients
    void *context = zmq_ctx_new ();
    void *publischer = zmq_socket (context, ZMQ_PUB);
    int rc = zmq_bind (publischer, "tcp://*:5556");
    assert (rc == 0);

    while(1) {
        cout << "loop"<<endl;
        for (int i = 0; i < 10; i++) {
            usleep(300000);
            zmq_send (publischer, "status", sizeof("status"), ZMQ_SNDMORE);
            zmq_send (publischer, "All is well", sizeof("All is well"), 0);
            cout << "status"<<endl;
        }
        sleep(1);
        zmq_send (publischer, "status", sizeof("status"), ZMQ_SNDMORE);
        zmq_send (publischer, "Faield xy", sizeof("Faield xy"), 0);
        cout << "status"<<endl;
        zmq_send (publischer, "error", sizeof("error"), ZMQ_SNDMORE);
        zmq_send (publischer, "Failed to set XXY", sizeof("failed to set XXY"), 0);
        cout << "error"<<endl;
    }
    return 0;
}