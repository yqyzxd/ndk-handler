//
// Created by 史浩 on 2019-12-21.
//

#include "MessageQueue.h"
#include "../utils/Log.h"
#define LOG_TAG "MessageQueue"

MessageQueue::MessageQueue() {
    init();
}

MessageQueue::MessageQueue(const char *queueName) {
    init();
    this->queueName = queueName;
}

MessageQueue::~MessageQueue() {}
void MessageQueue::init() {
    pthread_mutex_init(&mLock, NULL);
    pthread_cond_init(&mCondition, NULL);
    mNbPackets = 0;
    mFirst = NULL;
    mLast = NULL;
    mAbortRequest = false;
}

int MessageQueue::size() {
    pthread_mutex_lock(&mLock);
    int size = mNbPackets;
    pthread_mutex_unlock(&mLock);
    return size;
}

void MessageQueue::abort() {
    pthread_mutex_lock(&mLock);
    mAbortRequest = true;
    pthread_cond_signal(&mCondition);//让dequeueMessage得以继续运行
    pthread_mutex_unlock(&mLock);
}

int MessageQueue::enqueueMessage(Message *message) {


    if (mAbortRequest) {
        delete message;
        return -1;
    }
    pthread_mutex_lock(&mLock);
    MessageNode *node = new MessageNode();
    node->msg = message;
    node->next = NULL;

    if (mFirst == NULL) {
        mFirst = node;
    } else {

        /*插入最后一个
         * 从头开始找到最后一个
        */
        MessageNode *prev = mFirst;

        for (;;) {

            MessageNode *next = prev->next;
            if (next == NULL) {
                break;
            }
            prev = next;
        }

        prev->next = node;
    }

    mNbPackets++;
    //通知有数据了，dequeueMessage方法可以继续执行了
    pthread_cond_signal(&mCondition);
    pthread_mutex_unlock(&mLock);
    return 0;


}

int MessageQueue::dequeueMessage(Message **msg) {
    pthread_mutex_lock(&mLock);
    int ret;
    for (;;) {

        if (mAbortRequest) {
            ret = 1;
            break;
        }

        //找到第一个消息
        if (!mFirst) {
            LOGE("dequeueMessage pthread_cond_wait");
            //没有消息，则等待
            pthread_cond_wait(&mCondition, &mLock);
        } else {
            *msg = mFirst->msg;
            MessageNode *node = mFirst;
            mFirst = node->next;
            delete node;
            ret = 0;
            LOGE("dequeueMessage get it");
            break;
        }
        mNbPackets--;
    }

    pthread_mutex_unlock(&mLock);
    return ret;

}


void MessageQueue::flush() {


    MessageNode *curNode, *nextNode;
    Message *msg;
    pthread_mutex_lock(&mLock);

    for (curNode = mFirst; curNode != NULL; curNode = nextNode) {
        // 一个一个node清理
        msg = curNode->msg;
        if (msg != NULL) {
            delete msg;
        }
        nextNode = curNode->next;
        delete curNode;
        curNode = NULL;

    }
    mFirst=NULL;
    mNbPackets=0;
    pthread_mutex_unlock(&mLock);
}


