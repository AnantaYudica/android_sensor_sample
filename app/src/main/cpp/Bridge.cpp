//
// Created by Ananta Yudica on 20/12/2019.
//

#include "jni.h"
#include <android/log.h>

extern "C"
jint Java_com_example_android_1sensor_1sample_Native_onCreate(
    JNIEnv* pEnv,
    jobject pThis)
{
    __android_log_print(ANDROID_LOG_INFO, "native", "onCreate()");
    return 1;
}

extern "C"
jint Java_com_example_android_1sensor_1sample_Native_onStart(
    JNIEnv* pEnv,
    jobject pThis)
{
    __android_log_print(ANDROID_LOG_INFO, "native", "onStart()");
    return 1;
}

extern "C"
jint Java_com_example_android_1sensor_1sample_Native_onResume(
        JNIEnv* pEnv,
        jobject pThis)
{
    __android_log_print(ANDROID_LOG_INFO, "native", "onResume()");
    return 1;
}

extern "C"
jint Java_com_example_android_1sensor_1sample_Native_onPause(
        JNIEnv* pEnv,
        jobject pThis)
{
    __android_log_print(ANDROID_LOG_INFO, "native", "onPause()");
    return 1;
}

extern "C"
jint Java_com_example_android_1sensor_1sample_Native_onStop(
        JNIEnv* pEnv,
        jobject pThis)
{
    __android_log_print(ANDROID_LOG_INFO, "native", "onStop()");
    return 1;
}

extern "C"
jint Java_com_example_android_1sensor_1sample_Native_onRestart(
        JNIEnv* pEnv,
        jobject pThis)
{
    __android_log_print(ANDROID_LOG_INFO, "native", "onRestart()");
    return 1;
}

extern "C"
jint Java_com_example_android_1sensor_1sample_Native_onDestroy(
        JNIEnv* pEnv,
        jobject pThis)
{
    __android_log_print(ANDROID_LOG_INFO, "native", "onDestroy()");
    return 1;
}

extern "C"
jint Java_com_example_android_1sensor_1sample_Native_update(
        JNIEnv* pEnv,
        jobject pThis)
{

    return 1;
}
