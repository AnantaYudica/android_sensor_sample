//
// Created by Ananta Yudica on 12/01/2020.
//

#include "Gyroscope.h"

#include <utility>

namespace sensor_event
{

Gyroscope::Gyroscope() :
    Default{}
{}

Gyroscope::Gyroscope(std::shared_ptr<ASensorEvent> sensorEvents,
    const size_t & size) :
        Default(sensorEvents, size)
{}

Gyroscope::~Gyroscope()
{}

Gyroscope::Gyroscope(const Gyroscope & cpy) :
    Default(cpy)
{}

Gyroscope::Gyroscope(Gyroscope && mov) :
    Default(std::move(mov))
{}

Gyroscope::Gyroscope(const Default & cpy) :
    Default(cpy)
{}

Gyroscope::Gyroscope(Default && mov) :
    Default(std::move(mov))
{}

Gyroscope & Gyroscope::operator=(const Gyroscope & cpy)
{
    Default::operator=(cpy);
    return *this;
}

Gyroscope & Gyroscope::operator=(Gyroscope && mov)
{
    Default::operator=(std::move(mov));
    return *this;
}

Gyroscope & Gyroscope::operator=(const Default & cpy)
{
    Default::operator=(cpy);
    return *this;
}

Gyroscope & Gyroscope::operator=(Default && mov)
{
    Default::operator=(std::move(mov));
    return *this;
}

const float & Gyroscope::X(const size_t & i) const
{
    return m_sensorEvents.get()[i].vector.x;
}

const float & Gyroscope::Y(const size_t & i) const
{
    return m_sensorEvents.get()[i].vector.y;
}

const float & Gyroscope::Z(const size_t & i) const
{
    return m_sensorEvents.get()[i].vector.z;
}

} //!sensor_event
