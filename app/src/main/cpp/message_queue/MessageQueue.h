//
// Created by 史浩 on 2019-12-21.
//

#ifndef NDK_HANDLER_MESSAGEQUEUE_H
#define NDK_HANDLER_MESSAGEQUEUE_H

#include <pthread.h>
#include "Message.h"

#define MESSAGE_QUEUE_LOOP_QUIT_FLAG        19900909
class Handler;


typedef struct MessageNode{
    Message* msg;
    struct MessageNode* next;

    MessageNode(){
        msg=NULL;
        next= NULL;
    }
} MessageNode;

class MessageQueue {

public:
    MessageQueue();
    MessageQueue(const char* queueName);
    ~MessageQueue();



private:
    MessageNode* mFirst;
    MessageNode* mLast;
    int mNbPackets;//队列元素个数
    bool mAbortRequest; //是否请求停止
    pthread_mutex_t mLock;  //创建一把锁
    pthread_cond_t mCondition; //创建一把锁的条件
    const char* queueName;
public:
    int enqueueMessage(Message* message);
    int dequeueMessage(Message** msg);
    void init();//初始化成员变量
    void flush();//清空messagequeue
    int size(); //返回队列元素个数
    void abort();//停止
};


#endif //NDK_HANDLER_MESSAGEQUEUE_H
