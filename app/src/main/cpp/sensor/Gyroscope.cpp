//
// Created by Ananta Yudica on 12/01/2020.
//

#include "Gyroscope.h"

#include "../Log.h"
#include <utility>

namespace sensor
{

int Gyroscope::__CallbackDefault(const Sensor &,
    const sensor_event::Gyroscope &, const std::size_t &)
{
    return 0;
}

Gyroscope::Gyroscope(ASensor const* ptr) :
    Sensor(ptr),
    m_callback(&Gyroscope::__CallbackDefault)
{
    LOG_DEBUG("sensor::Gyroscope", "constructor(...)");
}

Gyroscope::Gyroscope(ASensor const* ptr, CallbackType callback) :
    Sensor(ptr),
    m_callback((callback ? callback : &Gyroscope::__CallbackDefault))
{
    LOG_DEBUG("sensor::Gyroscope", "constructor(...)");
}

Gyroscope::Gyroscope(const Gyroscope & cpy) :
    Sensor(cpy),
    m_callback(cpy.m_callback)
{
    LOG_DEBUG("sensor::Gyroscope", "copy constructor(...)");
}

Gyroscope::Gyroscope(Gyroscope && mov) :
    Sensor(std::move(mov)),
    m_callback(mov.m_callback)
{
    LOG_DEBUG("sensor::Gyroscope", "move constructor(...)");
    mov.m_callback = &Gyroscope::__CallbackDefault;
}

Gyroscope::~Gyroscope()
{
    LOG_DEBUG("sensor::MagneticField", "destructor(...)");
    m_callback = &Gyroscope::__CallbackDefault;
}

void Gyroscope::SetCallback(CallbackType callback)
{
    if (callback) m_callback = callback;
}

typename Gyroscope::CallbackType
Gyroscope::GetCallback()
{
    return m_callback;
}

int Gyroscope::Callback(sensor_event::Default events, std::size_t size)
{
    return m_callback(*this, static_cast<sensor_event::Gyroscope>(events), size);
}

} //!sensor
