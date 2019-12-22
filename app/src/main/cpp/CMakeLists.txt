cmake_minimum_required(VERSION 3.4.1)


file(GLOB message_queue_files message_queue/*.cpp)
file(GLOB egl_core_files egl_core/*.cpp)

add_library(
        native-handler
        SHARED
        com_wind_ndk_handler_JHandler.cpp
        ${message_queue_files}
        ${egl_core_files}
        HandlerController.cpp
        MyHandler.cpp

)


find_library(
        log-lib
        log)

target_link_libraries(
        native-handler


        EGL
        GLESv2
        android
        z
        ${log-lib})