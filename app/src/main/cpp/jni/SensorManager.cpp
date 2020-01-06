//
// Created by Ananta Yudica on 02/01/2020.
//

#include "SensorManager.h"
#include "../Definition.h"
#include "sensor/Default.h"
#include "sensor/Accelerometer.h"

#include "jni.h"
#include "../Log.h"
#include <vector>

namespace bridge
{

SensorManager::SensorManager() :
    ::SensorManager()
{
    LOG_DEBUG("SensorManager", "Constructor(...)");
    Init();
}

SensorManager::~SensorManager()
{
    LOG_DEBUG("SensorManager", "Destructor(...)");
}

int SensorManager::InitSensor(const int & type, ::Sensor * & sensor, InfSensorType infsensor)
{
    LOG_DEBUG("SensorManager", "InitSensor(...)");
    if (sensor != nullptr) return 2;
    if (type == static_cast<int>(::sensor::Type::invalid))  return -1;
    if (type == static_cast<int>(::sensor::Type::accelerometer))
        sensor = new bridge::sensor::Accelerometer(infsensor);
    else
        sensor = new bridge::sensor::Default(infsensor);
    return 1;
}

} //!bridge

extern "C"
jboolean  Java_com_example_android_1sensor_1sample_SensorManager_hasInstance(
    JNIEnv* pEnv,
    jobject pThis)
{
    LOG_DEBUG("native/SensorManager", "hasInstance(...)");
    return SensorManager::HasInstance();
}

extern "C"
jint Java_com_example_android_1sensor_1sample_SensorManager_size(
    JNIEnv* pEnv,
    jobject pThis)
{
    LOG_DEBUG("native/SensorManager", "size(...)");
    return (int)SensorManager::GetInstance().Size();
}

extern "C"
jint Java_com_example_android_1sensor_1sample_SensorManager_findOne(
    JNIEnv* pEnv,
    jobject pThis,
    jint pVal)
{
    LOG_DEBUG("native/SensorManager", "findOne(...)");
    return (int)SensorManager::GetInstance().FindOne(pVal).first;
}

extern "C"
jintArray Java_com_example_android_1sensor_1sample_SensorManager_find(
    JNIEnv* pEnv,
    jobject pThis,
    jint pVal)
{
    LOG_DEBUG("native/SensorManager", "find(...)");
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
    LOG_DEBUG("native/SensorManager", "type(...)");
    return SensorManager::GetInstance()[pId].Type();
}

extern "C"
jint Java_com_example_android_1sensor_1sample_SensorManager_minDelay(
    JNIEnv* pEnv,
    jobject pThis,
    jint pId)
{
    LOG_DEBUG("native/SensorManager", "minDelay(...)");
    return SensorManager::GetInstance()[pId].MinDelay();
}

extern "C"
jfloat Java_com_example_android_1sensor_1sample_SensorManager_resolution(
    JNIEnv* pEnv,
    jobject pThis,
    jint pId)
{
    LOG_DEBUG("native/SensorManager", "resolution(...)");
    return SensorManager::GetInstance()[pId].Resolution();
}

extern "C"
jstring Java_com_example_android_1sensor_1sample_SensorManager_name(
    JNIEnv* pEnv,
    jobject pThis,
    jint pId)
{
    LOG_DEBUG("native/SensorManager", "name(...)");
    return pEnv->NewStringUTF(SensorManager::GetInstance()[pId].Name());
}

extern "C"
jstring Java_com_example_android_1sensor_1sample_SensorManager_vendor(
    JNIEnv* pEnv,
    jobject pThis,
    jint pId)
{
    LOG_DEBUG("native/SensorManager", "vendor(...)");
    return pEnv->NewStringUTF(SensorManager::GetInstance()[pId].Vendor());
}

extern "C"
jint Java_com_example_android_1sensor_1sample_SensorManager_lastErrorCode(
        JNIEnv* pEnv,
        jobject pThis,
        jint pId)
{
    LOG_DEBUG("native/SensorManager", "lastErrorCode(...)");
    return SensorManager::GetInstance().GetSensorEvent(pId).get().LastErrorCode();
}

extern "C"
void Java_com_example_android_1sensor_1sample_SensorManager_delay__II(
    JNIEnv* pEnv,
    jobject pThis,
    jint pId,
    jint pVal)
{
    LOG_DEBUG("native/SensorManager", "delay(...)");
    SensorManager::GetInstance().GetSensorEvent(pId).get().Delay((int)pVal);
}

extern "C"
jint Java_com_example_android_1sensor_1sample_SensorManager_delay__I(
    JNIEnv* pEnv,
    jobject pThis,
    jint pId)
{
    LOG_DEBUG("native/SensorManager", "delay(...)");
    return SensorManager::GetInstance().GetSensorEvent(pId).get().Delay();
}

extern "C"
void Java_com_example_android_1sensor_1sample_SensorManager_enable(
    JNIEnv* pEnv,
    jobject pThis,
    jint pId)
{
    LOG_DEBUG("native/SensorManager", "enable(...)");
    SensorManager::GetInstance().GetSensorEvent(pId).get().Enable();
}

extern "C"
void Java_com_example_android_1sensor_1sample_SensorManager_disable(
    JNIEnv* pEnv,
    jobject pThis,
    jint pId)
{
    LOG_DEBUG("native/SensorManager", "disable(...)");
    SensorManager::GetInstance().GetSensorEvent(pId).get().Disable();
}

extern "C"
void Java_com_example_android_1sensor_1sample_SensorManager_pause(
    JNIEnv* pEnv,
    jobject pThis,
    jint pId)
{
    LOG_DEBUG("native/SensorManager", "pause(...)");
    SensorManager::GetInstance().GetSensorEvent(pId).get().Pause();
}

extern "C"
void Java_com_example_android_1sensor_1sample_SensorManager_resume(
    JNIEnv* pEnv,
    jobject pThis,
    jint pId)
{
    LOG_DEBUG("native/SensorManager", "resume(...)");
    SensorManager::GetInstance().GetSensorEvent(pId).get().Resume();
}

extern "C"
void Java_com_example_android_1sensor_1sample_SensorManager_start(
    JNIEnv* pEnv,
    jobject pThis,
    jint pId)
{
    LOG_DEBUG("native/SensorManager", "start(...)");
    SensorManager::GetInstance().GetSensorEvent(pId).get().Start();
}

extern "C"
void Java_com_example_android_1sensor_1sample_SensorManager_stop(
    JNIEnv* pEnv,
    jobject pThis,
    jint pId)
{
    LOG_DEBUG("native/SensorManager", "stop(...)");
    SensorManager::GetInstance().GetSensorEvent(pId).get().Stop();
}

extern "C"
jboolean Java_com_example_android_1sensor_1sample_SensorManager_isError(
    JNIEnv* pEnv,
    jobject pThis,
    jint pId)
{
    LOG_DEBUG("native/SensorManager", "isError(...)");
    return SensorManager::GetInstance().GetSensorEvent(pId).get().IsError();
}

extern "C"
jboolean Java_com_example_android_1sensor_1sample_SensorManager_isEnable(
    JNIEnv* pEnv,
    jobject pThis,
    jint pId)
{
    LOG_DEBUG("native/SensorManager", "isEnable(...)");
    return SensorManager::GetInstance().GetSensorEvent(pId).get().IsEnable();
}

extern "C"
jboolean Java_com_example_android_1sensor_1sample_SensorManager_isPause(
    JNIEnv* pEnv,
    jobject pThis,
    jint pId)
{
    LOG_DEBUG("native/SensorManager", "isPause(...)");
    return SensorManager::GetInstance().GetSensorEvent(pId).get().IsPause();
}

extern "C"
jboolean Java_com_example_android_1sensor_1sample_SensorManager_isRun(
    JNIEnv* pEnv,
    jobject pThis,
    jint pId)
{
    LOG_DEBUG("native/SensorManager", "isRun(...)");
    return SensorManager::GetInstance().GetSensorEvent(pId).get().IsRun();
}

