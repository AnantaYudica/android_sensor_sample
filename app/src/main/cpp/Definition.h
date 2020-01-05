//
// Created by Ananta Yudica on 04/01/2020.
//

#ifndef ANDROID_SENSOR_SAMPLE_DEFINITION_H
#define ANDROID_SENSOR_SAMPLE_DEFINITION_H

#include "android/os/build/Version.h"

#include <android/sensor.h>

#include <memory>
#include <dlfcn.h>

typedef const ASensor * InfSensorType;

typedef ASensorManager * InfSensorManagerType;

typedef ASensorEventQueue * InfSensorEventQueueType;

typedef ALooper * InfLooperType;

typedef std::shared_ptr<ASensorEvent> InfSensorEventType;

typedef ASensorList InfSensorListType;

namespace sensor
{

inline void Reset(const ASensor * & inf)
{
    inf = nullptr;
}

inline bool IsDefault(const ASensor * const & inf)
{
    return inf == nullptr;
}

inline void GetType(const ASensor * & inf, int * out)
{
    *out = ASensor_getType(inf);
}

inline void GetMinimumDelay(const ASensor * & inf, int * out)
{
    *out = ASensor_getMinDelay(inf);
}

inline void GetResolution(const ASensor * & inf, float * out)
{
    *out = ASensor_getResolution(inf);
}

inline void GetName(const ASensor * & inf, const char ** out)
{
    *out = ASensor_getName(inf);
}

inline void GetVendor(const ASensor * & inf, const char ** out)
{
    *out = ASensor_getVendor(inf);
}

inline InfSensorEventType AllocateEvents(const size_t & size)
{
    return InfSensorEventType{new ASensorEvent[size],
        std::default_delete<ASensorEvent[]>{}};
}

inline ASensorList AllocateList(const size_t & size)
{
    if (size == 0) return nullptr;
    return new ASensor*[size];
}

inline void FreeList(ASensorList list)
{
    delete[] list;
}

enum class Type : int
{
    invalid =  ASENSOR_TYPE_INVALID,
    accelerometer = ASENSOR_TYPE_ACCELEROMETER,
    magnetic_field = ASENSOR_TYPE_MAGNETIC_FIELD,
    gyroscope = ASENSOR_TYPE_GYROSCOPE,
    light = ASENSOR_TYPE_LIGHT,
    pressure = ASENSOR_TYPE_PRESSURE,
    proximity = ASENSOR_TYPE_PROXIMITY,
    gravity = ASENSOR_TYPE_GRAVITY,
    linear_acceleration = ASENSOR_TYPE_LINEAR_ACCELERATION,
    rotation_vector = ASENSOR_TYPE_ROTATION_VECTOR,
    relative_humidity = ASENSOR_TYPE_RELATIVE_HUMIDITY,
    ambient_temperature = ASENSOR_TYPE_AMBIENT_TEMPERATURE,
    magnetic_field_uncalibrated = ASENSOR_TYPE_MAGNETIC_FIELD_UNCALIBRATED,
    game_rotation_vector = ASENSOR_TYPE_GAME_ROTATION_VECTOR,
    gyrosope_uncalibrated = ASENSOR_TYPE_GYROSCOPE_UNCALIBRATED,
    significant_motion = ASENSOR_TYPE_SIGNIFICANT_MOTION ,
    step_detector = ASENSOR_TYPE_STEP_DETECTOR,
    step_counter = ASENSOR_TYPE_STEP_COUNTER,
    geomagnetic_rotation_vector = ASENSOR_TYPE_GEOMAGNETIC_ROTATION_VECTOR,
    heart_rate = ASENSOR_TYPE_HEART_RATE,
    pose_6dof = ASENSOR_TYPE_POSE_6DOF,
    stationary_detect = ASENSOR_TYPE_STATIONARY_DETECT,
    motion_detect = ASENSOR_TYPE_MOTION_DETECT,
    heart_beat = ASENSOR_TYPE_HEART_BEAT,
    additional_info = ASENSOR_TYPE_ADDITIONAL_INFO,
    low_latency_offbody_detect = ASENSOR_TYPE_LOW_LATENCY_OFFBODY_DETECT,
    accelerometer_uncalibrated = ASENSOR_TYPE_ACCELEROMETER_UNCALIBRATED,
};

namespace manager
{

struct __Library
{
    void * handle;
    __Library(const char * library_name) :
        handle(nullptr)
    {
        handle = dlopen(library_name, RTLD_LAZY);
    }
    ~__Library()
    {
        if (handle)
            dlclose(handle);
        handle = nullptr;
    }
    template<typename TFunction>
    TFunction * GetFunctionPointer(const char * function_name)
    {
        if (!handle) return nullptr;
        return (TFunction*) dlsym(handle, function_name);
    }
};

inline void CreateEventQueue(ASensorManager* manager, ALooper* looper, int ident,
    ALooper_callbackFunc callback, void* data, ASensorEventQueue* * sensorEventQueue)
{
    *sensorEventQueue = ASensorManager_createEventQueue(manager, looper, ident,
            callback, data);
}

inline int DestroyEventQueue(ASensorManager* manager, ASensorEventQueue* queue)
{
    return ASensorManager_destroyEventQueue(manager, queue);
}

inline ASensorManager* GetInstance(const char * package)
{
    typedef ASensorManager* (GetInstanceFuncType)(const char *);
    static __Library lib("libandroid.so");
    static auto function_ptr =
        lib.GetFunctionPointer<GetInstanceFuncType>("ASensorManager_getInstanceForPackage");
    if (android::os::build::Version::SDK() >= 21)
    {
        if (function_ptr) return function_ptr(package);
    }
    return ASensorManager_getInstance();
}

inline int GetSensorList(ASensorManager* manager, ASensorList* list)
{
    return ASensorManager_getSensorList(manager, list);
}


} //!manager

namespace event
{

namespace queue
{

inline int EnableSensor(ASensorEventQueue* queue, ASensor const* sensor)
{
    return ASensorEventQueue_enableSensor(queue, sensor);
}

inline int DisableSensor(ASensorEventQueue* queue, ASensor const* sensor)
{
    return ASensorEventQueue_disableSensor(queue, sensor);
}

inline int SetEventRate(ASensorEventQueue* queue, ASensor const* sensor, int32_t usec)
{
    return ASensorEventQueue_setEventRate(queue, sensor, usec);
}

inline int HasEvents(ASensorEventQueue* queue)
{
    return ASensorEventQueue_hasEvents(queue);
}

inline ssize_t GetEvents(ASensorEventQueue* queue, InfSensorEventType events, size_t count)
{
    return ASensorEventQueue_getEvents(queue, events.get(), count);
}

} //!queue

} //!event

} //sensor

#endif //ANDROID_SENSOR_SAMPLE_DEFINITION_H
