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
    //3. 设置display配置？同时获取EGLConfig
    if(!eglChooseConfig(display,attrib_list,&config,1,&numConfigs)){
        return false;
    }
    EGLint context_attrib_list []= {EGL_CONTEXT_CLIENT_VERSION,2,
                                 EGL_NONE};
    //创建EGLContext
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

EGLSurface EGLCore::createWindowSurface(ANativeWindow *window) {
    EGLSurface surface=NULL;
    EGLint format;
    //获取format
    if (!eglGetConfigAttrib(display,config,EGL_NATIVE_VISUAL_ID,&format)){
        release();
        return surface;
    }
    //设置nativewind属性
    ANativeWindow_setBuffersGeometry(window,0,0,format);
    //EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, const EGLint *attrib_list
    surface=eglCreateWindowSurface(display,config,window,0);
    if(!surface){
        //error
    }
    return surface;

}

EGLSurface EGLCore::createOffscreenSurface(int width, int height) {
    EGLSurface  surface;
    EGLint attrib_list[]={EGL_WIDTH,width,
                          EGL_HEIGHT,height,
                          EGL_NONE};
    surface=eglCreatePbufferSurface(display,config,attrib_list);

    return surface;
}

bool EGLCore::makeCurrent(EGLSurface eglSurface) {
    return eglMakeCurrent(display,eglSurface,eglSurface,context);
}
void EGLCore::doneCurrent() {
    eglMakeCurrent(display,EGL_NO_SURFACE,EGL_NO_SURFACE,EGL_NO_CONTEXT);
}
bool EGLCore::swapBuffers(EGLSurface eglSurface) {
    return eglSwapBuffers(display,eglSurface);
}

EGLConfig EGLCore::getConfig() {
    return config;
}
EGLContext EGLCore::getContext() {
    return context;
}
EGLDisplay EGLCore::getDisplay() {
    return display;
}
