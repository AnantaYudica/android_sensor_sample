//
// Created by Ananta Yudica on 20/12/2019.
//

#ifndef ANDROID_SENSOR_SAMPLE_SENSORMANAGER_H
#define ANDROID_SENSOR_SAMPLE_SENSORMANAGER_H

#include "Sensor.h"
#include "SensorEvent.h"

#include <android/Sensor.h>
#include <vector>
#include <functional>
#include <utility>

class SensorManager
{
public:
    typedef size_t KeyType;
    typedef Sensor ValueType;
    typedef std::reference_wrapper<Sensor> ValueRefType;
    typedef std::reference_wrapper<SensorEvent> SensorEventRefType;
private:
    typedef ASensorManager* (GetInstanceForPackageType)(const char *);
private:
    static constexpr const char * ms_library_cstr = "libandroid.so";
private:
    static SensorManager * ms_instance;
    static void * ms_handle;
    static GetInstanceForPackageType * ms_getInstanceForPackage;
private:
    static ASensorManager * __GetAndroidInstance();
public:
    static SensorManager & CreateInstance();
    static SensorManager & GetInstance();
    static bool HasInstance();
    static void DestroyInstance();
    static void Open();
    static void Close();
private:
    Sensor ** m_sensors;
    SensorEvent ** m_sensorEvents;
    ASensorManager * m_sensorManager;
    size_t m_sensorsSize;
private:
    void Init();
    bool InitSensorManager();
    bool InitSensors();
private:
    SensorManager();
public:
    ~SensorManager();
public:
    size_t Size() const;
    std::pair<KeyType, ValueRefType> FindOne(const int & type);
    std::vector<std::pair<KeyType, ValueRefType>> Find(const int & type);
public:
    SensorEventRefType GetSensorEvent(const KeyType & key);
    SensorEventRefType GetSensorEvent(const KeyType & key, const int & delay);
public:
    void OnStart();
    void OnStop();
    void OnPause();
    void OnResume();
public:
    ValueType& operator[](const KeyType & key);
    const ValueType& operator[](const KeyType & key) const;
};



#endif //ANDROID_SENSOR_SAMPLE_SENSORMANAGER_H
