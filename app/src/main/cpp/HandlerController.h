//
// Created by 史浩 on 2019-12-21.
//

#ifndef NDK_HANDLER_HANDLERCONTROLLER_H
#define NDK_HANDLER_HANDLERCONTROLLER_H

#include <pthread.h>
#include "message_queue/MessageQueue.h"
//#include "MyHandler.h"
class MyHandler;
class HandlerController {
public:
    HandlerController();
    ~HandlerController();


    bool sendMessage(int what);

    void loop();
    void doLoop();
    void print();
private:
    pthread_t loopPThread;
    MyHandler* handler;
    MessageQueue* queue;
};


#endif //NDK_HANDLER_HANDLERCONTROLLER_H
