//
// Created by Ananta Yudica on 28/12/2019.
//

#include <android/sensor.h>
#include "Default.h"

namespace sensor_event
{

Default::Default() :
    m_sensorEvents(nullptr),
    m_size(0)
{}

Default::Default(std::shared_ptr<ASensorEvent> sensorEvents, const size_t & size) :
    m_sensorEvents(sensorEvents),
    m_size(size)
{}

Default::~Default()
{
    m_sensorEvents = nullptr;
    m_size = 0;
}

Default::Default(const Default & cpy) :
    m_sensorEvents(cpy.m_sensorEvents),
    m_size(cpy.m_size)
{}

Default::Default(Default && mov) :
    m_sensorEvents(mov.m_sensorEvents),
    m_size(mov.m_size)
{
    mov.m_sensorEvents = nullptr;
    mov.m_size = 0;
}

Default & Default::operator=(const Default & cpy)
{
    m_sensorEvents = cpy.m_sensorEvents;
    m_size = cpy.m_size;
    return *this;
}

Default & Default::operator=(Default && mov)
{
    m_sensorEvents = mov.m_sensorEvents;
    m_size = mov.m_size;
    mov.m_sensorEvents = nullptr;
    mov.m_size = 0;
    return *this;
}

void Default::SetEvents(std::shared_ptr<ASensorEvent> data, const size_t & size)
{
    m_sensorEvents = data;
    m_size = size;
}

size_t Default::Size() const
{
    return m_size;
}

const int32_t& Default::Version(const size_t & i) const
{
    return m_sensorEvents.get()[i].version;
}

const int32_t& Default::Sensor(const size_t & i) const
{
    return m_sensorEvents.get()[i].sensor;
}

const int32_t& Default::Type(const size_t & i) const
{
    return m_sensorEvents.get()[i].type;
}

const int32_t& Default::Reserved0(const size_t & i) const
{
    return m_sensorEvents.get()[i].reserved0;
}

const int64_t& Default::Timestamp(const size_t & i) const
{
    return m_sensorEvents.get()[i].timestamp;
}

const uint64_t (&Default::Data(const size_t & i) const)[8]
{
    return m_sensorEvents.get()[i].u64.data;
}

const uint32_t& Default::Flags(const size_t & i) const
{
    return m_sensorEvents.get()[i].flags;
}

const int32_t (&Default::Reserved1(const size_t & i) const)[3]
{
    return m_sensorEvents.get()[i].reserved1;
}

Default::operator bool() const
{
    return m_sensorEvents != nullptr;
}

bool Default::operator==(const Default & other) const
{
    return m_sensorEvents.get() == other.m_sensorEvents.get();
}

bool Default::operator!=(const Default & other) const
{
    return m_sensorEvents.get() != other.m_sensorEvents.get();
}

} //!sensor_event
