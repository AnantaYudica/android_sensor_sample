//
// Created by Ananta Yudica on 25/12/2019.
//

#include "Accelerometer.h"
#include "../Log.h"
#include <utility>

namespace sensor
{

int Accelerometer::__CallbackDefault(const Sensor &, const sensor_event::Accelerometer &,
        const std::size_t &)
{
    return 0;
}

Accelerometer::Accelerometer(ASensor const* ptr) :
    Sensor(ptr),
    m_callback(&Accelerometer::__CallbackDefault)
{
    LOG_DEBUG("sensor::Accelerometer", "constructor(...)");
}

Accelerometer::Accelerometer(ASensor const* ptr, CallbackType callback) :
    Sensor(ptr),
    m_callback((callback ? callback : &Accelerometer::__CallbackDefault))
{
    LOG_DEBUG("sensor::Accelerometer", "constructor(...)");
}

Accelerometer::Accelerometer(const Accelerometer & cpy) :
    Sensor(cpy),
    m_callback(cpy.m_callback)
{
    LOG_DEBUG("sensor::Accelerometer", "copy constructor(...)");
}

Accelerometer::Accelerometer(Accelerometer && mov) :
        Sensor(std::move(mov)),
        m_callback(mov.m_callback)
{
    LOG_DEBUG("sensor::Accelerometer", "move constructor(...)");
    mov.m_callback = &Accelerometer::__CallbackDefault;
}

Accelerometer::~Accelerometer()
{
    LOG_DEBUG("sensor::Accelerometer", "destructor(...)");
    m_callback = &Accelerometer::__CallbackDefault;
}
void Accelerometer::SetCallback(CallbackType callback)
{
    if (callback) m_callback = callback;
}

typename Accelerometer::CallbackType Accelerometer::GetCallback()
{
    return m_callback;
}

int Accelerometer::Callback(sensor_event::Default events, std::size_t size)
{
    return m_callback(*this, static_cast<sensor_event::Accelerometer>(events), size);
}

}
