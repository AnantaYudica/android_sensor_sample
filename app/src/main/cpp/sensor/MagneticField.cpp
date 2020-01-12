//
// Created by Ananta Yudica on 12/01/2020.
//

#include "MagneticField.h"
#include "../Log.h"
#include <utility>

namespace sensor
{

int MagneticField::__CallbackDefault(const Sensor &,
    const sensor_event::MagneticField &, const std::size_t &)
{
    return 0;
}

MagneticField::MagneticField(ASensor const* ptr) :
    Sensor(ptr),
    m_callback(&MagneticField::__CallbackDefault)
{
    LOG_DEBUG("sensor::MagneticField", "constructor(...)");
}

MagneticField::MagneticField(ASensor const* ptr, CallbackType callback) :
    Sensor(ptr),
    m_callback(callback)
{
    LOG_DEBUG("sensor::MagneticField", "constructor(...)");
}

MagneticField::MagneticField(const MagneticField & cpy) :
    Sensor(cpy),
    m_callback(cpy.m_callback)
{
    LOG_DEBUG("sensor::MagneticField", "copy constructor(...)");
}

MagneticField::MagneticField(MagneticField && mov) :
    Sensor(std::move(mov)),
    m_callback(mov.m_callback)
{
    LOG_DEBUG("sensor::MagneticField", "move constructor(...)");
    mov.m_callback = &MagneticField::__CallbackDefault;
}

MagneticField::~MagneticField()
{
    LOG_DEBUG("sensor::MagneticField", "destructor(...)");
    m_callback = &MagneticField::__CallbackDefault;
}

void MagneticField::SetCallback(CallbackType callback)
{
    if (callback) m_callback = callback;
}

typename MagneticField::CallbackType
MagneticField::GetCallback()
{
    return m_callback;
}

int MagneticField::Callback(sensor_event::Default events, std::size_t size)
{
    return m_callback(*this, static_cast<sensor_event::MagneticField>(events), size);
}

} //!sensor
