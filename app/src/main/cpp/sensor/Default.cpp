//
// Created by Ananta Yudica on 25/12/2019.
//

#include "Default.h"
#include "../Log.h"
#include <utility>

namespace sensor
{

int Default::__CallbackDefault(const Sensor &, const sensor_event::Default &,
       const std::size_t &)
{
    return 0;
}

Default::Default(ASensor const* ptr) :
    Sensor(ptr),
    m_callback(&Default::__CallbackDefault)
{
    LOG_DEBUG("sensor::Default", "constructor(...)");
}

Default::Default(ASensor const* ptr, CallbackType callback) :
    Sensor(ptr),
    m_callback(callback)
{
    LOG_DEBUG("sensor::Default", "constructor(...)");
}

Default::Default(const Default & cpy) :
    Sensor(cpy),
    m_callback(cpy.m_callback)
{
    LOG_DEBUG("sensor::Default", "copy constructor(...)");
}

Default::Default(Default && mov) :
    Sensor(std::move(mov)),
    m_callback(mov.m_callback)
{
    LOG_DEBUG("sensor::Default", "move constructor(...)");
    mov.m_callback = &Default::__CallbackDefault;
}

Default::~Default()
{
    LOG_DEBUG("sensor::Default", "destructor(...)");
    m_callback = &Default::__CallbackDefault;
}
void Default::SetCallback(CallbackType callback)
{
    if (callback) m_callback = callback;
}

typename Default::CallbackType Default::GetCallback()
{
    return m_callback;
}

int Default::Callback(sensor_event::Default events, std::size_t size)
{
    return m_callback(*this, events, size);
}

} //!sensor
