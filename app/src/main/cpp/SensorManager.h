//
// Created by Ananta Yudica on 20/12/2019.
//

#ifndef ANDROID_SENSOR_SAMPLE_SENSORMANAGER_H
#define ANDROID_SENSOR_SAMPLE_SENSORMANAGER_H

#include "Sensor.h"
#include "SensorEvent.h"
#include "Definition.h"
#include "Log.h"

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
    typedef std::pair<KeyType, ValueRefType> PairValueType;
    typedef std::vector<PairValueType> ListPairValueType;
private:
    static SensorManager * ms_instance;
public:
    template<typename TDerived, typename ... TArgs>
    static SensorManager & CreateInstance(TArgs && ... args);
    static SensorManager & GetInstance();
    static bool HasInstance();
    static void DestroyInstance();
private:
    Sensor ** m_sensors;
    SensorEvent ** m_sensorEvents;
    InfSensorManagerType m_sensorManager;
    size_t m_sensorsSize;
protected:
    void Init();
private:
    bool InitSensorManager();
    bool InitSensors();
protected:
    virtual int InitSensor(const int & type, ::Sensor * & sensor, InfSensorType infsensor) = 0;
protected:
    SensorManager();
public:
    virtual ~SensorManager();
public:
    size_t Size() const;
    PairValueType FindOne(const int & type);
    ListPairValueType Find(const int & type);
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

template<typename TDerived, typename ... TArgs>
SensorManager & SensorManager::CreateInstance(TArgs && ... args)
{
    LOG_DEBUG("SensorManger", "SensorManager::CreateInstance(...)");
    if (!ms_instance)
        ms_instance = new TDerived(std::forward<TArgs>(args)...);
    return *ms_instance;
}



#endif //ANDROID_SENSOR_SAMPLE_SENSORMANAGER_H
