//
// Created by Ananta Yudica on 20/12/2019.
//

#include "SensorManager.h"
#include "Sensor.h"

#include <android/Sensor.h>
#include <android/log.h>

SensorManager * SensorManager::ms_instance = nullptr;

SensorManager & SensorManager::CreateInstance()
{
    if (!ms_instance)
        ms_instance = new SensorManager();
    return *ms_instance;
}

SensorManager & SensorManager::GetInstance()
{
    return *ms_instance;
}

void SensorManager::DestroyInstance()
{
    if (ms_instance) delete ms_instance;
    ms_instance = nullptr;
}

void SensorManager::Init()
{
    auto a_sensor_manager = ASensorManager_getInstance();
    if (!a_sensor_manager) return;
    const auto size = ASensorManager_getSensorList(a_sensor_manager, nullptr);
    if (!InitSensor(size)) return;
    ASensorList a_sensor_list = new ASensor*[size];
    ASensorManager_getSensorList(a_sensor_manager, &a_sensor_list);
    for (auto i = 0; i < size; ++i)
    {
        m_sensors[i] = new Sensor(a_sensor_list[i]);
    }
    delete[] a_sensor_list;
}

bool SensorManager::InitSensor(const size_t & size)
{
    if (m_sensors || size == 0) return false;
    m_sensorsSize = size;
    m_sensors = new Sensor*[size];
    return true;
}

SensorManager::SensorManager() :
    m_sensors(nullptr),
    m_sensorsSize(0)
{
    Init();
}

SensorManager::~SensorManager()
{
    for (auto i = 0; i < m_sensorsSize; ++i)
        delete m_sensors[i];
    if (m_sensors) delete[] m_sensors;
    m_sensorsSize = 0;
    m_sensors = nullptr;
}

size_t SensorManager::Size() const
{
    return m_sensorsSize;
}

std::pair<SensorManager::KeyType, SensorManager::ValueRefType>
SensorManager::FindOne(const int & type)
{
    static Sensor empty{nullptr};
    for (auto i = 0; i < m_sensorsSize; ++i)
    {
        if (m_sensors[i]->Type() == type)
            return {i, ValueRefType(*(m_sensors[i]))};
    }
    return {size_t(-1), ValueRefType{empty}};
}

std::vector<std::pair<SensorManager::KeyType, SensorManager::ValueRefType>>
SensorManager::Find(const int & type)
{
    std::vector<std::pair<KeyType, ValueRefType>> res;
    for (auto i = 0; i < m_sensorsSize; ++i)
    {
        if (m_sensors[i]->Type() == type)
            res.push_back(std::pair<KeyType, ValueRefType>(i, *(m_sensors[i])));
    }
    return res;
}

SensorManager::ValueType& SensorManager::operator[](const KeyType & key)
{
    return *(m_sensors[key]);
}

const SensorManager::ValueType& SensorManager::operator[](const KeyType & key) const
{
    return *(m_sensors[key]);
}
