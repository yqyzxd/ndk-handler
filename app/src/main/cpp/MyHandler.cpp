//
// Created by 史浩 on 2019-12-21.
//

#include "MyHandler.h"

MyHandler::MyHandler(MessageQueue* queue,HandlerController *controller):Handler(queue),controller(controller){
}
MyHandler::~MyHandler() {

}

void MyHandler::handleMessage(Message *message) {

    switch (message->getWhat()){
        case MESSAGE_WHAT_PRINT:
            controller->print();
            break;
    }

}