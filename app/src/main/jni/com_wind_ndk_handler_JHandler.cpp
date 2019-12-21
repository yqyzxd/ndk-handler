//
// Created by 史浩 on 2019-12-21.
//
#include "com_wind_ndk_handler_JHandler.h"
#include "../cpp/HandlerController.h"

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jlong JNICALL Java_com_wind_ndk_handler_JHandler_native_1init
        (JNIEnv *, jobject) {

    HandlerController *controller = new HandlerController();
    controller->loop();
    return reinterpret_cast<jlong>(controller);
}


JNIEXPORT jboolean JNICALL Java_com_wind_ndk_handler_JHandler_native_1send_1message
        (JNIEnv *, jobject, jlong native_handle, jint jwhat) {

    HandlerController *controller= (HandlerController *)(native_handle);
    return controller->sendMessage((int)jwhat);
}

#ifdef __cplusplus
}
#endif
