//
// Created by Ananta Yudica on 20/12/2019.
//

#include "SensorManager.h"
#include "Sensor.h"
#include "android/os/build/Version.h"
#include "Log.h"

#include <android/Sensor.h>

#include <dlfcn.h>

SensorManager * SensorManager::ms_instance = nullptr;

void * SensorManager::ms_handle = nullptr;

ASensorManager* (*SensorManager::ms_getInstanceForPackage)(const char *) = nullptr;

ASensorManager * SensorManager::__GetAndroidInstance()
{
    static ASensorManager* (*GetInstanceFunc)(const char *) = nullptr;
    static const char * package = "android_sensor_sample.sensormanager";
    if (android::os::build::Version::SDK() >= 21)
    {
        if (ms_getInstanceForPackage)
            return ms_getInstanceForPackage(package);
    }
    return ASensorManager_getInstance();
}

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

void SensorManager::DestroyInstance()
{
    LOG_DEBUG("SensorManger", "SensorManager::DestroyInstance(...)");
    if (ms_instance) delete ms_instance;
    ms_instance = nullptr;
}
void SensorManager::Open()
{
    LOG_DEBUG("SensorManger", "SensorManager::Open(...)");
    if (!ms_handle)
    {
        ms_handle = dlopen(ms_library_cstr, RTLD_LAZY);
        LOG_DEBUG("SensorManger", "handle : %p", ms_handle);

        if (ms_handle)
            ms_getInstanceForPackage = (GetInstanceForPackageType *) dlsym(ms_handle,
                    "ASensorManager_getInstanceForPackage");

        LOG_DEBUG("SensorManger", "ASensorManager_getInstanceForPackage : %p",
                (void *)ms_getInstanceForPackage);
    }
}

void SensorManager::Close()
{
    LOG_DEBUG("SensorManger", "SensorManager::Close(...)");
    if (ms_handle)
        dlclose(ms_handle);
    ms_handle = nullptr;
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
    m_sensorManager = __GetAndroidInstance();
    return m_sensorManager != nullptr;
}

bool SensorManager::InitSensors()
{
    LOG_DEBUG("SensorManger", "SensorManager::InitSensors(...)");
    const auto size = ASensorManager_getSensorList(m_sensorManager, nullptr);
    if (size == 0) return false;
    m_sensorsSize = size;
    m_sensors = new Sensor*[size];
    ASensorList a_sensor_list = new ASensor*[size];
    ASensorManager_getSensorList(m_sensorManager, &a_sensor_list);
    for (auto i = 0; i < size; ++i)
    {
        m_sensors[i] = new Sensor(a_sensor_list[i]);
    }
    delete[] a_sensor_list;
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
