//
// Created by 史浩 on 2019-12-21.
//

#include "HandlerController.h"
#include "utils/Log.h"
#include "MyHandler.h"
#define LOG_TAG "HandlerController"
HandlerController::HandlerController() {
    queue=new MessageQueue();
    handler=new MyHandler(queue,this);
}

HandlerController::~HandlerController() {

}
void* loopThread(void* args){

    HandlerController* controller= static_cast<HandlerController *>(args);
    controller->doLoop();
    return 0;
}

void HandlerController::loop() {

    pthread_create(&loopPThread,0,loopThread,this);

}

void HandlerController::doLoop() {
   while (true){
       Message* msg = NULL;
       LOGE("doLoop before dequeueMessage");
       int ret=this->queue->dequeueMessage(&msg);
       LOGE("doLoop after dequeueMessage");

       ret=msg->execute();
       if (ret==MESSAGE_QUEUE_LOOP_QUIT_FLAG){
           break;
       }

   }
    LOGE("loop finish");
}

bool HandlerController::sendMessage(int what) {
    Message* message=new Message(what);
    int ret=handler->postMessage(message);
    if (ret==0){
        return true;
    }
    return false;
}
void HandlerController::print() {
    LOGE("doPrint");
}