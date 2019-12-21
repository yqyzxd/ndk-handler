//
// Created by 史浩 on 2019-12-21.
//

#include "Handler.h"
#include "./Message.h"

Handler::Handler(MessageQueue *queue) {
    this->queue=queue;
}

Handler::~Handler() {
    queue->flush();
    delete queue;
}

int Handler::postMessage(Message *message) {
    message->target = this;
    return queue->enqueueMessage(message);
}
