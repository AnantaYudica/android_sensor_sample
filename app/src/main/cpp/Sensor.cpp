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
    static auto array_deleter = [](char * ptr) {delete[] ptr;};
    val = std::shared_ptr<char>(new char[size + 1], array_deleter);
    strncpy(val.get(), cstr, size);
    val.get()[size] = '\0';
}

Sensor::Sensor(ASensor * ptr) :
    m_type(ASENSOR_TYPE_INVALID),
    m_minDelay(-1),
    m_resolution(0.0),
    m_name(nullptr),
    m_vendor(nullptr),
    m_ptr(ptr)
{
    LOG_DEBUG("sensor", "constructor(...)");
    if(ptr) Init(ptr);
}

Sensor::Sensor(const Sensor & cpy) :
    m_type(cpy.m_type),
    m_minDelay(cpy.m_minDelay),
    m_resolution(cpy.m_resolution),
    m_name(cpy.m_name),
    m_vendor(cpy.m_vendor),
    m_ptr(cpy.m_ptr)
{
    LOG_DEBUG("sensor", "copy constructor(...)");
}

Sensor::Sensor(Sensor && mov) :
    m_type(mov.m_type),
    m_minDelay(mov.m_minDelay),
    m_resolution(mov.m_resolution),
    m_name(mov.m_name),
    m_vendor(mov.m_vendor),
    m_ptr(mov.m_ptr)
{
    LOG_DEBUG("sensor", "move constructor(...)");
    mov.m_type = ASENSOR_TYPE_INVALID;
    mov.m_minDelay = -1;
    mov.m_resolution = 0.0;
    mov.m_name = nullptr;
    mov.m_vendor = nullptr;
    mov.m_ptr = nullptr;
}

Sensor::~Sensor()
{
    LOG_DEBUG("sensor", "destructor(...)");
    m_type = ASENSOR_TYPE_INVALID;
    m_minDelay = -1;
    m_resolution = 0.0;
    m_name = nullptr;
    m_vendor = nullptr;
    m_ptr = nullptr;
}

void Sensor::Init(ASensor * ptr)
{
    LOG_DEBUG("sensor", "Init(...)");
    InitType(ptr);
    InitMinDelay(ptr);
    InitResolution(ptr);
    InitName(ptr);
    InitVendor(ptr);
}

void Sensor::InitType(ASensor * ptr)
{
    LOG_DEBUG("sensor", "InitType(...)");
    m_type = ASensor_getType(ptr);
    LOG_DEBUG("sensor", "type = %d", m_type);
}

void Sensor::InitMinDelay(ASensor * ptr)
{
    LOG_DEBUG("sensor", "InitMinDelay(...)");
    m_minDelay = ASensor_getMinDelay(ptr);
    LOG_DEBUG("sensor", "min delay = %d", m_minDelay);
}

void Sensor::InitResolution(ASensor * ptr)
{
    LOG_DEBUG("sensor", "InitResolution(...)");
    m_resolution = ASensor_getResolution(ptr);
    LOG_DEBUG("sensor", "resolution = %f", m_resolution);
}

void Sensor::InitName(ASensor * ptr)
{
    LOG_DEBUG("sensor", "InitName(...)");
    const char * cstr = ASensor_getName(ptr);
    const size_t  size = cstr ? strnlen(cstr, 1024): 0;
    __SetValueSharedString(m_name, cstr, size);
    LOG_DEBUG("sensor", "name = \"%s\"", m_name.get());
}

void Sensor::InitVendor(ASensor * ptr)
{
    LOG_DEBUG("sensor", "InitVendor(...)");
    const char * cstr = ASensor_getVendor(ptr);
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

ASensor * Sensor::Pointer()
{
    return m_ptr;
}

Sensor::operator bool() const
{
    return m_ptr != nullptr;
}

bool Sensor::operator==(const Sensor & sensor) const
{
    return m_ptr == sensor.m_ptr;
}

bool Sensor::operator!=(const Sensor & sensor) const
{
    return m_ptr != sensor.m_ptr;
}
