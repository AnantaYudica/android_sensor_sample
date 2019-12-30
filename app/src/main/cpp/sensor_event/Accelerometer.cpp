//
// Created by Ananta Yudica on 29/12/2019.
//

#include "Accelerometer.h"

#include <utility>

namespace sensor_event
{

Accelerometer::Accelerometer() :
    Default{}
{}

Accelerometer::Accelerometer(std::shared_ptr<ASensorEvent> sensorEvents,
    const size_t & size) :
        Default(sensorEvents, size)
{}

Accelerometer::~Accelerometer()
{}

Accelerometer::Accelerometer(const Accelerometer & cpy) :
    Default(cpy)
{}

Accelerometer::Accelerometer(Accelerometer && mov) :
    Default(std::move(mov))
{}

Accelerometer::Accelerometer(const Default & cpy) :
    Default(cpy)
{}

Accelerometer::Accelerometer(Default && mov) :
    Default(std::move(mov))
{}

Accelerometer & Accelerometer::operator=(const Accelerometer & cpy)
{
    Default::operator=(cpy);
    return *this;
}

Accelerometer & Accelerometer::operator=(Accelerometer && mov)
{
    Default::operator=(std::move(mov));
    return *this;
}

Accelerometer & Accelerometer::operator=(const Default & cpy)
{
    Default::operator=(cpy);
    return *this;
}

Accelerometer & Accelerometer::operator=(Default && mov)
{
    Default::operator=(std::move(mov));
    return *this;
}

const float & Accelerometer::X(const size_t & i) const
{
    return m_sensorEvents.get()[i].acceleration.x;
}

const float & Accelerometer::Y(const size_t & i) const
{
    return m_sensorEvents.get()[i].acceleration.y;
}

const float & Accelerometer::Z(const size_t & i) const
{
    return m_sensorEvents.get()[i].acceleration.z;
}

} //!sensor_event
