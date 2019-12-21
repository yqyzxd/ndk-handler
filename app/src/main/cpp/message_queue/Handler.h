//
// Created by 史浩 on 2019-12-21.
//

#ifndef NDK_HANDLER_HANDLER_H
#define NDK_HANDLER_HANDLER_H


#include "MessageQueue.h"

class Handler {
public:
    Handler(MessageQueue* queue);
    ~Handler();

    /**
     * 将message加入MessageQueue
     * @param message
     * @return
     */
    int postMessage(Message* message);
    /**
     * 子类继承去实现不同的功能
     */
    virtual void handleMessage(Message* message)=0;

private:
    MessageQueue* queue;
};


#endif //NDK_HANDLER_HANDLER_H
