//  Hello World client
#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void * context;
void *requester;
void apiSend(char *toSend,int size, void * context_ ){
    if(size <=5){
        printf("error\r\n");
    }
    printf("send :   %s\r\n",toSend);
    char buff[64] = {0,};
    int s;
    if((s = zmq_send (requester, toSend,size, 0))<0){
        printf("error send ret: %d, %d, %s\r\n",s, zmq_errno(), zmq_strerror(zmq_errno()));
    }
    memset(buff,0,64);
    if((s=zmq_recv (requester, buff, 64, 0))<0){
        printf("error gets  ret: %d , %d %s\r\n",s, zmq_errno(),zmq_strerror(zmq_errno()));
    }
}
int apiGet(char * request,int size, void* context_){
    char buff[64] = {0,};
    zmq_send (requester, request, size, 0);
    memset(buff,0,64);
    size = zmq_recv (requester, buff, 64, 0);
    // expect "ok: XX"
    int data = -1;
    if(size >0 && strstr(buff,"ok:")!= NULL){
         data = atoi(buff);
        //printf ("Received ok with data: %d\r\n", data);

    }
    return data;

}

/**
 * ObjMapper *objectMapper;
conveyorbeltStation *c6 = new conveyorbeltStation(nullptr,"End");
PushStation *c5 = new PushStation(c6,"Pusher2");
MillAndDrillStation *c4 = new MillAndDrillStation(c5,"Drill");
MillAndDrillStation *c3 = new MillAndDrillStation(c4,"Mill");
PushStation *c2 = new PushStation(c3,"Pusher1");
conveyorbeltStation *c1 = new conveyorbeltStation(c2,"Start");
 */
char s1[] = "Start";
char s2[] = "Pusher1";
char s3[] = "Mill";
char s4[] = "Drill";
char s5[] = "Pusher2";
char s6[] = "End";
void runOneTime(){
    printf("run one time \r\n");
    char buff[128];
    int s = sprintf(buff,"set %s 0 1",s1); // start conv1
    apiSend(buff,s,context);
    uint8_t hasBox = 0;
    for(int i = 0; i<5000;i++){
        int s = sprintf(buff,"get %s 0 ",s1); // get l1
        if (apiGet(buff,s,context))
            hasBox = 1;
        usleep(1000);
    }
    s = sprintf(buff,"set %s 0 0",s1); // stop conv1
    apiSend(buff,s,context);
    if(!hasBox){
        return;
    }
    // PUSHER 1 Forward
    s = sprintf(buff,"set %s 0 1",s2); // start conv1
    apiSend(buff,s,context);
    do{
        int s = sprintf(buff,"get %s 1 ",s2); // get pusher 1 back
        hasBox = apiGet(buff,s,context);
        usleep(1000);
    } while (!hasBox);
    s = sprintf(buff,"set %s 0 0",s2); // start conv1
    apiSend(buff,s,context);
    s = sprintf(buff,"set %s 1 1",s2); // start conv1
    apiSend(buff,s,context);
}

int main (void)
{
    printf ("Connecting to hello world server…\n");
    context = zmq_ctx_new ();
    if (!context) {
        printf ("Error occurred during zmq_init(): %s\n", zmq_strerror (errno));
        exit (-1);
    }
    requester = zmq_socket (context, ZMQ_REQ);
    if (!requester) {
        printf ("Error occurred during zmq_init(): %s\n", zmq_strerror (errno));
        exit (-2);
    }
    assert(zmq_connect(requester, "tcp://localhost:5556") == 0);

    while(1){
        runOneTime();
        sleep(1);

    }
    zmq_close (requester);
    zmq_ctx_destroy (context);
    return 0;
}