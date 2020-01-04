//
// Created by Ananta Yudica on 21/12/2019.
//

#include "Sensor.h"
#include "Log.h"

#include <android/Sensor.h>
#include <cstring>

void Sensor::__SetValueSharedString(std::shared_ptr<char> & val, const char * cstr,
        const size_t & size)
{
    val = std::shared_ptr<char>(new char[size + 1], std::default_delete<char[]>{});
    strncpy(val.get(), cstr, size);
    val.get()[size] = '\0';
}

Sensor::Sensor(InfSensorType inf) :
    m_type(static_cast<int>(sensor::Type::invalid)),
    m_minDelay(-1),
    m_resolution(0.0),
    m_name(nullptr),
    m_vendor(nullptr),
    m_inf(inf)
{
    LOG_DEBUG("sensor", "constructor(...)");
    if(inf) Init(inf);
}

Sensor::Sensor(const Sensor & cpy) :
    m_type(cpy.m_type),
    m_minDelay(cpy.m_minDelay),
    m_resolution(cpy.m_resolution),
    m_name(cpy.m_name),
    m_vendor(cpy.m_vendor),
    m_inf(cpy.m_inf)
{
    LOG_DEBUG("sensor", "copy constructor(...)");
}

Sensor::Sensor(Sensor && mov) :
    m_type(mov.m_type),
    m_minDelay(mov.m_minDelay),
    m_resolution(mov.m_resolution),
    m_name(mov.m_name),
    m_vendor(mov.m_vendor),
    m_inf(mov.m_inf)
{
    LOG_DEBUG("sensor", "move constructor(...)");
    mov.m_type = static_cast<int>(sensor::Type::invalid);
    mov.m_minDelay = -1;
    mov.m_resolution = 0.0;
    mov.m_name = nullptr;
    mov.m_vendor = nullptr;
    mov.m_inf = nullptr;
}

Sensor::~Sensor()
{
    LOG_DEBUG("sensor", "destructor(...)");
    m_type = static_cast<int>(sensor::Type::invalid);
    m_minDelay = -1;
    m_resolution = 0.0;
    m_name = nullptr;
    m_vendor = nullptr;
    sensor::Reset(m_inf);
}

void Sensor::Init(InfSensorType inf)
{
    LOG_DEBUG("sensor", "Init(...)");
    InitType(inf);
    InitMinDelay(inf);
    InitResolution(inf);
    InitName(inf);
    InitVendor(inf);
}

void Sensor::InitType(InfSensorType inf)
{
    LOG_DEBUG("sensor", "InitType(...)");
    sensor::GetType(inf, &m_type);
    LOG_DEBUG("sensor", "type = %d", m_type);
}

void Sensor::InitMinDelay(InfSensorType inf)
{
    LOG_DEBUG("sensor", "InitMinDelay(...)");
    sensor::GetMinimumDelay(inf, &m_minDelay);
    LOG_DEBUG("sensor", "min delay = %d", m_minDelay);
}

void Sensor::InitResolution(InfSensorType inf)
{
    LOG_DEBUG("sensor", "InitResolution(...)");
    sensor::GetResolution(inf, &m_resolution);
    LOG_DEBUG("sensor", "resolution = %f", m_resolution);
}

void Sensor::InitName(InfSensorType inf)
{
    LOG_DEBUG("sensor", "InitName(...)");
    const char * cstr = nullptr;
    sensor::GetName(inf, cstr);
    const size_t  size = cstr ? strnlen(cstr, 1024): 0;
    __SetValueSharedString(m_name, cstr, size);
    LOG_DEBUG("sensor", "name = \"%s\"", m_name.get());
}

void Sensor::InitVendor(InfSensorType inf)
{
    LOG_DEBUG("sensor", "InitVendor(...)");
    const char * cstr = nullptr;
    sensor::GetVendor(inf, cstr);
    const size_t  size = cstr ? strnlen(cstr, 1024): 0;
    __SetValueSharedString(m_vendor, cstr, size);
    LOG_DEBUG("sensor", "vendor = \"%s\"", m_vendor.get());
}

int Sensor::Type() const
{
    return m_type;
}

int Sensor::MinDelay() const
{
    return m_minDelay;
}

float Sensor::Resolution() const
{
    return m_resolution;
}

const char * Sensor::Name() const
{
    return m_name.get();
}

const char * Sensor::Vendor() const
{
    return m_vendor.get();
}

InfSensorType Sensor::Interface()
{
    return m_inf;
}

Sensor::operator bool() const
{
    return !sensor::IsDefault(m_inf);
}

bool Sensor::operator==(const Sensor & sensor) const
{
    return m_inf == sensor.m_inf;
}

bool Sensor::operator!=(const Sensor & sensor) const
{
    return m_inf != sensor.m_inf;
}
