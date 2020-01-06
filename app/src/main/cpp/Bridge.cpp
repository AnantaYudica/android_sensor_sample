//
// Created by Ananta Yudica on 20/12/2019.
//

#include "android/os/build/Version.h"
#include "Information.h"
#include "jni/SensorManager.h"

#include "jni.h"
#include "Log.h"

extern "C"
jint Java_com_example_android_1sensor_1sample_Native_onCreate(
    JNIEnv* pEnv,
    jobject pThis)
{
    LOG_DEBUG("native", "onCreate()");
    Information::CreateInstance("android", pEnv);
    android::os::build::Version::Load(pEnv);
    SensorManager::CreateInstance<bridge::SensorManager>();
    return 1;
}

extern "C"
jint Java_com_example_android_1sensor_1sample_Native_onStart(
    JNIEnv* pEnv,
    jobject pThis)
{
    LOG_DEBUG("native", "onStart()");
    SensorManager::GetInstance().OnStart();
    return 1;
}

extern "C"
jint Java_com_example_android_1sensor_1sample_Native_onResume(
        JNIEnv* pEnv,
        jobject pThis)
{
    LOG_DEBUG("native", "onResume()");
    SensorManager::GetInstance().OnResume();
    return 1;
}

extern "C"
jint Java_com_example_android_1sensor_1sample_Native_onPause(
        JNIEnv* pEnv,
        jobject pThis)
{
    LOG_DEBUG("native", "onPause()");
    SensorManager::GetInstance().OnPause();
    return 1;
}

extern "C"
jint Java_com_example_android_1sensor_1sample_Native_onStop(
        JNIEnv* pEnv,
        jobject pThis)
{
    LOG_DEBUG("native", "onStop()");
    SensorManager::GetInstance().OnStop();
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
    android::os::build::Version::Reset();
    SensorManager::DestroyInstance();
    Information::DestroyInstance();
    return 1;
}

extern "C"
jint Java_com_example_android_1sensor_1sample_Native_update(
        JNIEnv* pEnv,
        jobject pThis)
{

    return 1;
}
