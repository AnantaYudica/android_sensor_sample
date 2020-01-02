//
// Created by Ananta Yudica on 02/01/2020.
//

#include "../SensorManager.h"

#include "jni.h"
#include "../Log.h"
#include <vector>

extern "C"
jboolean  Java_com_example_android_1sensor_1sample_SensorManager_hasInstance(
    JNIEnv* pEnv,
    jobject pThis)
{
    return SensorManager::HasInstance();
}

extern "C"
jint Java_com_example_android_1sensor_1sample_SensorManager_size(
    JNIEnv* pEnv,
    jobject pThis)
{
    return (int)SensorManager::GetInstance().Size();
}

extern "C"
jint Java_com_example_android_1sensor_1sample_SensorManager_findOne(
    JNIEnv* pEnv,
    jobject pThis,
    jint pVal)
{
    return (int)SensorManager::GetInstance().FindOne(pVal).first;
}

extern "C"
jintArray Java_com_example_android_1sensor_1sample_SensorManager_find(
    JNIEnv* pEnv,
    jobject pThis,
    jint pVal)
{
    jintArray res;
    size_t size = 0;
    typename SensorManager::ListPairValueType list;
    if (SensorManager::HasInstance())
    {
        list = SensorManager::GetInstance().Find(pVal);
        size = list.size();
        res = pEnv->NewIntArray(size);
        for (auto i = 0; i < size; ++i)
            pEnv->SetIntArrayRegion(res, i, 1, (int*)(&list[i].first));
    }
    else res = pEnv->NewIntArray(0);
    return res;
}

extern "C"
jint Java_com_example_android_1sensor_1sample_SensorManager_type(
    JNIEnv* pEnv,
    jobject pThis,
    jint pId)
{
    return SensorManager::GetInstance()[pId].Type();
}

extern "C"
jint Java_com_example_android_1sensor_1sample_SensorManager_minDelay(
    JNIEnv* pEnv,
    jobject pThis,
    jint pId)
{
    return SensorManager::GetInstance()[pId].MinDelay();
}

extern "C"
jfloat Java_com_example_android_1sensor_1sample_SensorManager_resolution(
    JNIEnv* pEnv,
    jobject pThis,
    jint pId)
{
    return SensorManager::GetInstance()[pId].Resolution();
}

extern "C"
jstring Java_com_example_android_1sensor_1sample_SensorManager_name(
    JNIEnv* pEnv,
    jobject pThis,
    jint pId)
{
    return pEnv->NewStringUTF(SensorManager::GetInstance()[pId].Name());
}

extern "C"
jstring Java_com_example_android_1sensor_1sample_SensorManager_vendor(
    JNIEnv* pEnv,
    jobject pThis,
    jint pId)
{
    return pEnv->NewStringUTF(SensorManager::GetInstance()[pId].Vendor());
}

extern "C"
jint Java_com_example_android_1sensor_1sample_SensorManager_lastErrorCode(
        JNIEnv* pEnv,
        jobject pThis,
        jint pId)
{
    return SensorManager::GetInstance().GetSensorEvent(pId).get().LastErrorCode();
}

extern "C"
void Java_com_example_android_1sensor_1sample_SensorManager_delay__II(
    JNIEnv* pEnv,
    jobject pThis,
    jint pId,
    jint pVal)
{
    SensorManager::GetInstance().GetSensorEvent(pId).get().Delay((int)pVal);
}

extern "C"
jint Java_com_example_android_1sensor_1sample_SensorManager_delay__I(
    JNIEnv* pEnv,
    jobject pThis,
    jint pId)
{
    return SensorManager::GetInstance().GetSensorEvent(pId).get().Delay();
}

extern "C"
void Java_com_example_android_1sensor_1sample_SensorManager_enable(
    JNIEnv* pEnv,
    jobject pThis,
    jint pId)
{
    SensorManager::GetInstance().GetSensorEvent(pId).get().Enable();
}

extern "C"
void Java_com_example_android_1sensor_1sample_SensorManager_disable(
    JNIEnv* pEnv,
    jobject pThis,
    jint pId)
{
    SensorManager::GetInstance().GetSensorEvent(pId).get().Disable();
}

extern "C"
void Java_com_example_android_1sensor_1sample_SensorManager_pause(
    JNIEnv* pEnv,
    jobject pThis,
    jint pId)
{
    SensorManager::GetInstance().GetSensorEvent(pId).get().Pause();
}

extern "C"
void Java_com_example_android_1sensor_1sample_SensorManager_resume(
    JNIEnv* pEnv,
    jobject pThis,
    jint pId)
{
    SensorManager::GetInstance().GetSensorEvent(pId).get().Resume();
}

extern "C"
void Java_com_example_android_1sensor_1sample_SensorManager_start(
    JNIEnv* pEnv,
    jobject pThis,
    jint pId)
{
    SensorManager::GetInstance().GetSensorEvent(pId).get().Start();
}

extern "C"
void Java_com_example_android_1sensor_1sample_SensorManager_stop(
    JNIEnv* pEnv,
    jobject pThis,
    jint pId)
{
    SensorManager::GetInstance().GetSensorEvent(pId).get().Stop();
}

extern "C"
jboolean Java_com_example_android_1sensor_1sample_SensorManager_isError(
    JNIEnv* pEnv,
    jobject pThis,
    jint pId)
{
    return SensorManager::GetInstance().GetSensorEvent(pId).get().IsError();
}

extern "C"
jboolean Java_com_example_android_1sensor_1sample_SensorManager_isEnable(
    JNIEnv* pEnv,
    jobject pThis,
    jint pId)
{
    return SensorManager::GetInstance().GetSensorEvent(pId).get().IsEnable();
}

extern "C"
jboolean Java_com_example_android_1sensor_1sample_SensorManager_isPause(
    JNIEnv* pEnv,
    jobject pThis,
    jint pId)
{
    return SensorManager::GetInstance().GetSensorEvent(pId).get().IsPause();
}

extern "C"
jboolean Java_com_example_android_1sensor_1sample_SensorManager_isRun(
    JNIEnv* pEnv,
    jobject pThis,
    jint pId)
{
    return SensorManager::GetInstance().GetSensorEvent(pId).get().IsRun();
}

