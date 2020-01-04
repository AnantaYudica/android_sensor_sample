//
// Created by Ananta Yudica on 04/01/2020.
//

#ifndef ANDROID_SENSOR_SAMPLE_DEFINITION_H
#define ANDROID_SENSOR_SAMPLE_DEFINITION_H

#include <android/sensor.h>

typedef const ASensor * InfSensorType;

namespace sensor
{

inline void Reset(const ASensor * & inf)
{
    inf = nullptr;
}

inline bool IsDefault(const ASensor * & inf)
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

inline void GetName(const ASensor * & inf, const char *& out)
{
    *out = ASensor_getName(inf);
}

inline void GetVendor(const ASensor * & inf, const char *& out)
{
    *out = ASensor_getVendor(inf);
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

} //sensor

#endif //ANDROID_SENSOR_SAMPLE_DEFINITION_H
