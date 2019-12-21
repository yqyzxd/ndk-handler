//
// Created by 史浩 on 2019-12-21.
//

#ifndef NDK_HANDLER_MESSAGE_H
#define NDK_HANDLER_MESSAGE_H

class Handler;

class Message {

public:
    Message(int what);
    Message(int what,int arg1,int arg2,void* obj);
    ~Message();
    //发送该message的Handler
    Handler* target;
private:
    int what;
    int arg1;
    int arg2;
    void* obj;



public:
    /**
     * 执行target的handleMessage方法
     * @return
     */
    int execute();

    int getWhat();
    int getArg1();
    int getArg2();
    void* getObj();
};



#endif //NDK_HANDLER_MESSAGE_H
