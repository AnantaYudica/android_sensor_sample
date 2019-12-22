//
// Created by Ananta Yudica on 20/12/2019.
//

#ifndef ANDROID_SENSOR_SAMPLE_SENSORMANAGER_H
#define ANDROID_SENSOR_SAMPLE_SENSORMANAGER_H

#include "Sensor.h"

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
private:
    static SensorManager * ms_instance;
public:
    static SensorManager & CreateInstance();
    static SensorManager & GetInstance();
    static void DestroyInstance();
private:
    Sensor ** m_sensors;
    size_t m_sensorsSize;
private:
    void Init();
    bool InitSensor(const size_t & size);
private:
    SensorManager();
public:
    ~SensorManager();
public:
    size_t Size() const;
    std::pair<KeyType, ValueRefType> FindOne(const int & type);
    std::vector<std::pair<KeyType, ValueRefType>> Find(const int & type);
public:
    ValueType& operator[](const KeyType & key);
    const ValueType& operator[](const KeyType & key) const;
};



#endif //ANDROID_SENSOR_SAMPLE_SENSORMANAGER_H
