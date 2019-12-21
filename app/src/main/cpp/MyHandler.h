//
// Created by 史浩 on 2019-12-21.
//

#ifndef NDK_HANDLER_MYHANDLER_H
#define NDK_HANDLER_MYHANDLER_H


#include "message_queue/Handler.h"

#include "./HandlerController.h"

#define MESSAGE_WHAT_PRINT 1

class MyHandler: public Handler {
public:

    MyHandler(MessageQueue* queue,HandlerController* controller);
    ~MyHandler();
    virtual void handleMessage(Message* message);

private:
    HandlerController* controller;
};


#endif //NDK_HANDLER_MYHANDLER_H
