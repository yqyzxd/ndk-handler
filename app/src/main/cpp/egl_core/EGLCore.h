//
// Created by 史浩 on 2019-12-21.
//

#ifndef NDK_HANDLER_EGLCORE_H
#define NDK_HANDLER_EGLCORE_H

#include <android/native_window.h>

typedef EGLBoolean (EGLAPIENTRYP PFNEGLPRESENTATIONTIMEANDROIDPROC)(EGLDisplay display, EGLSurface surface, khronos_stime_nanoseconds_t time);

class EGLCore {


public:
    EGLCore();
    ~EGLCore();
    /**
     * 初始化  EGLContext
     * @return
     */
    bool init();
    bool init(EGLContext shareContext);
    /**
     * 通过window创建EGLSurface
     * @param window
     * @return
     */
    EGLSurface createWindowSurface(ANativeWindow* window);
    EGLSurface createOffscreenSurface(int width,int height);

    /**
     * 操作当前EGLSurface
     * @param eglSurface
     * @return
     */
    bool makeCurrent(EGLSurface eglSurface);
    void doneCurrent();

    /**
     * 交换帧缓冲区，使当前eglsurface推到帧缓存区
     * @param eglSurface
     * @return
     */
    bool swapBuffers(EGLSurface eglSurface);
    /**
     * 是否当前的EGLSurface
     * @param eglSurface
     */
    void releaseSurface(EGLSurface eglSurface);
    /**
     * 释放EGLContext 等
     */
    void release();



public:
    EGLContext getContext();
    EGLDisplay getDisplay();
    EGLConfig getConfig();

private:
    EGLContext context;
    EGLDisplay display;
    EGLConfig config;

    //设置时间戳的函数
    PFNEGLPRESENTATIONTIMEANDROIDPROC pfneglPresentationTimeANDROID;
};


#endif //NDK_HANDLER_EGLCORE_H
