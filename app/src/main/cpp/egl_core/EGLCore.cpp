//
// Created by 史浩 on 2019-12-21.
//
#include <EGL/egl.h>
#include "EGLCore.h"
#include "../utils/Log.h"
#define LOG_TAG "EGLCore"
EGLCore::EGLCore() {

    context=EGL_NO_CONTEXT;
    display=EGL_NO_DISPLAY;
    config=NULL;
}

EGLCore::~EGLCore() {

}


bool EGLCore::init() {
    init(NULL);
}
bool EGLCore::init(EGLContext shareContext) {
    //1. 获取Display
    display=eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if(display==EGL_NO_DISPLAY){
        return false;
    }
    //2. 初始化Display
    eglInitialize(display,0,0);

    EGLint numConfigs;
    EGLint attrib_list[]={
            EGL_BUFFER_SIZE,32,
            EGL_ALPHA_SIZE,8,
            EGL_BLUE_SIZE,8,
            EGL_GREEN_SIZE,8,
            EGL_RED_SIZE,8,
            EGL_RENDERABLE_TYPE,EGL_OPENGL_ES2_BIT,
            EGL_SURFACE_TYPE,EGL_WINDOW_BIT,
            EGL_NONE
    };
    //3. 设置display配置？
    if(!eglChooseConfig(display,attrib_list,&config,1,&numConfigs)){
        return false;
    }
    EGLint context_attrib_list []= {EGL_CONTEXT_CLIENT_VERSION,2,
                                 EGL_NONE};
    context=eglCreateContext(display,config,shareContext==NULL?EGL_NO_CONTEXT:shareContext,
                     context_attrib_list );

    if (context==NULL){
        return false;
    }
    pfneglPresentationTimeANDROID = (PFNEGLPRESENTATIONTIMEANDROIDPROC)eglGetProcAddress("eglPresentationTimeANDROID");
    if (!pfneglPresentationTimeANDROID) {
        LOGE("eglPresentationTimeANDROID is not available!");
    }
}