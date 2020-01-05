//
// Created by Ananta Yudica on 20/12/2019.
//

#include "SensorManager.h"
#include "Sensor.h"
#include "sensor/Default.h"
#include "android/os/build/Version.h"
#include "Log.h"

#include <android/Sensor.h>

#include <dlfcn.h>

SensorManager * SensorManager::ms_instance = nullptr;

SensorManager & SensorManager::CreateInstance()
{
    LOG_DEBUG("SensorManger", "SensorManager::CreateInstance(...)");
    if (!ms_instance)
        ms_instance = new SensorManager();
    return *ms_instance;
}

SensorManager & SensorManager::GetInstance()
{
    return *ms_instance;
}

bool SensorManager::HasInstance()
{
    return ms_instance != nullptr;
}

void SensorManager::DestroyInstance()
{
    LOG_DEBUG("SensorManger", "SensorManager::DestroyInstance(...)");
    if (ms_instance) delete ms_instance;
    ms_instance = nullptr;
}

void SensorManager::Init()
{
    LOG_DEBUG("SensorManger", "SensorManager::Init(...)");
    if (!InitSensorManager()) return;
    InitSensors();
}

bool SensorManager::InitSensorManager()
{
    LOG_DEBUG("SensorManger", "SensorManager::InitSensorManager(...)");
    m_sensorManager = sensor::manager::GetInstance("android_sensor_sample.sensormanager");
    return m_sensorManager != nullptr;
}

bool SensorManager::InitSensors()
{
    LOG_DEBUG("SensorManger", "SensorManager::InitSensors(...)");
    const auto size = sensor::manager::GetSensorList(m_sensorManager, nullptr);
    if (size == 0) return false;
    m_sensorsSize = size;
    m_sensors = new Sensor*[size];
    m_sensorEvents = new SensorEvent*[size];
    InfSensorListType sensor_list = sensor::AllocateList(size);
    sensor::manager::GetSensorList(m_sensorManager, &sensor_list);
    for (auto i = 0; i < size; ++i)
    {
        m_sensors[i] = new sensor::Default(sensor_list[i]);
        m_sensorEvents[i] = nullptr;
    }
    sensor::FreeList(sensor_list);
    return true;
}

SensorManager::SensorManager() :
    m_sensors(nullptr),
    m_sensorManager(nullptr),
    m_sensorsSize(0)
{
    LOG_DEBUG("SensorManger", "Constructor(...)");
    Init();
}

SensorManager::~SensorManager()
{
    LOG_DEBUG("SensorManger", "Destructor(...)");
    for (auto i = 0; i < m_sensorsSize; ++i)
    {
        delete m_sensors[i];
        if (m_sensorEvents[i]) delete m_sensorEvents[i];
    }
    if (m_sensors) delete[] m_sensors;
    if (m_sensorEvents) delete[] m_sensorEvents;
    m_sensorsSize = 0;
    m_sensors = nullptr;
}

size_t SensorManager::Size() const
{
    return m_sensorsSize;
}

typename SensorManager::PairValueType
SensorManager::FindOne(const int & type)
{
    static sensor::Default empty{nullptr};
    for (auto i = 0; i < m_sensorsSize; ++i)
    {
        if (m_sensors[i]->Type() == type)
            return {i, ValueRefType(*(m_sensors[i]))};
    }
    return {size_t(-1), ValueRefType{empty}};
}

typename SensorManager::ListPairValueType
SensorManager::Find(const int & type)
{
    ListPairValueType res;
    for (auto i = 0; i < m_sensorsSize; ++i)
    {
        if (m_sensors[i]->Type() == type)
            res.push_back(std::pair<KeyType, ValueRefType>(i, *(m_sensors[i])));
    }
    return res;
}

typename SensorManager::SensorEventRefType
SensorManager::GetSensorEvent(const KeyType & key)
{
    if (!m_sensorEvents[key])
        m_sensorEvents[key] = new SensorEvent(m_sensorManager, m_sensors[key]);
    return SensorEventRefType(*(m_sensorEvents[key]));
}

typename SensorManager::SensorEventRefType
SensorManager::GetSensorEvent(const KeyType & key, const int & delay)
{
    if (!m_sensorEvents[key])
        m_sensorEvents[key] = new SensorEvent(m_sensorManager, m_sensors[key], delay);
    return SensorEventRefType(*(m_sensorEvents[key]));
}

void SensorManager::OnStart()
{
    for (auto i = 0; i < m_sensorsSize; ++i)
    {
        if (m_sensorEvents[i]) m_sensorEvents[i]->Start();
    }
}

void SensorManager::OnStop()
{
    for (auto i = 0; i < m_sensorsSize; ++i)
    {
        if (m_sensorEvents[i]) m_sensorEvents[i]->Stop();
    }
}

void SensorManager::OnPause()
{
    for (auto i = 0; i < m_sensorsSize; ++i)
    {
        if (m_sensorEvents[i]) m_sensorEvents[i]->Pause();
    }
}

void SensorManager::OnResume()
{
    for (auto i = 0; i < m_sensorsSize; ++i)
    {
        if (m_sensorEvents[i]) m_sensorEvents[i]->Resume();
    }
}

SensorManager::ValueType& SensorManager::operator[](const KeyType & key)
{
    return *(m_sensors[key]);
}

const SensorManager::ValueType& SensorManager::operator[](const KeyType & key) const
{
    return *(m_sensors[key]);
}
