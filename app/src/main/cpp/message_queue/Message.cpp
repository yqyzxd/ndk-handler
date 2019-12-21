//
// Created by 史浩 on 2019-12-21.
//

#include "Message.h"
#include "Handler.h"
#include "../utils/Log.h"
#define LOG_TAG "Message"
Message::Message(int what) {
    this->what=what;
    this->arg1=0;
    this->arg2=0;
    this->obj= NULL;

    target=NULL;
}

Message::Message(int what, int arg1, int arg2, void *obj) {
    this->what=what;
    this->arg1=arg1;
    this->arg2=arg2;
    this->obj=obj;
}

Message::~Message() {

}

int Message::execute() {
    //退出loop循环标记
    LOGE("execute start");
    if(what==MESSAGE_QUEUE_LOOP_QUIT_FLAG){
        return MESSAGE_QUEUE_LOOP_QUIT_FLAG;
    } else if(target){
        LOGE("execute handleMessage");
        target->handleMessage(this);
        return 1;
    }
    LOGE("execute finish");
    return 0;

}

int Message::getArg1() {
    return arg1;
}
int Message::getArg2() {
    return arg2;
}
int Message::getWhat() {
    return what;
}
void* Message::getObj() {
    return obj;
}