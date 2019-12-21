package com.wind.ndk.handler;

/**
 * Created By wind
 * on 2019-12-21
 */
public class JHandler {


    static {
        System.loadLibrary("native-handler");
    }
    private long mHandle;
    public JHandler(){
        mHandle= native_init();
    }

    public boolean sendMessage(int what){
        return native_send_message(mHandle,what);
    }

    private native long native_init();
    private native boolean native_send_message(long handle,int what);

}
