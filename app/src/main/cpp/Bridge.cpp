//
// Created by Ananta Yudica on 20/12/2019.
//

#include "jni.h"
#include "Log.h"

extern "C"
jint Java_com_example_android_1sensor_1sample_Native_onCreate(
    JNIEnv* pEnv,
    jobject pThis)
{
    LOG_DEBUG("native", "onCreate()");
    return 1;
}

extern "C"
jint Java_com_example_android_1sensor_1sample_Native_onStart(
    JNIEnv* pEnv,
    jobject pThis)
{
    LOG_DEBUG("native", "onStart()");
    return 1;
}

extern "C"
jint Java_com_example_android_1sensor_1sample_Native_onResume(
        JNIEnv* pEnv,
        jobject pThis)
{
    LOG_DEBUG("native", "onResume()");
    return 1;
}

extern "C"
jint Java_com_example_android_1sensor_1sample_Native_onPause(
        JNIEnv* pEnv,
        jobject pThis)
{
    LOG_DEBUG("native", "onPause()");
    return 1;
}

extern "C"
jint Java_com_example_android_1sensor_1sample_Native_onStop(
        JNIEnv* pEnv,
        jobject pThis)
{
    LOG_DEBUG("native", "onStop()");
    return 1;
}

extern "C"
jint Java_com_example_android_1sensor_1sample_Native_onRestart(
        JNIEnv* pEnv,
        jobject pThis)
{
    LOG_DEBUG("native", "onRestart()");
    return 1;
}

extern "C"
jint Java_com_example_android_1sensor_1sample_Native_onDestroy(
        JNIEnv* pEnv,
        jobject pThis)
{
    LOG_DEBUG("native", "onDestroy()");
    return 1;
}

extern "C"
jint Java_com_example_android_1sensor_1sample_Native_update(
        JNIEnv* pEnv,
        jobject pThis)
{

    return 1;
}
