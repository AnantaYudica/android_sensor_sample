//
// Created by Ananta Yudica on 11/01/2020.
//

#include "MagneticField.h"

#include <utility>

namespace sensor_event
{

MagneticField::MagneticField() :
    Default{}
{}

MagneticField::MagneticField(std::shared_ptr<ASensorEvent> sensorEvents,
    const size_t & size) :
        Default(sensorEvents, size)
{}

MagneticField::~MagneticField()
{}

MagneticField::MagneticField(const MagneticField & cpy) :
    Default(cpy)
{}

MagneticField::MagneticField(MagneticField && mov) :
    Default(std::move(mov))
{}

MagneticField::MagneticField(const Default & cpy) :
    Default(cpy)
{}

MagneticField::MagneticField(Default && mov) :
    Default(std::move(mov))
{}

MagneticField & MagneticField::operator=(const MagneticField & cpy)
{
    Default::operator=(cpy);
    return *this;
}

MagneticField & MagneticField::operator=(MagneticField && mov)
{
    Default::operator=(std::move(mov));
    return *this;
}

MagneticField & MagneticField::operator=(const Default & cpy)
{
    Default::operator=(cpy);
    return *this;
}

MagneticField & MagneticField::operator=(Default && mov)
{
    Default::operator=(std::move(mov));
    return *this;
}

const float & MagneticField::X(const size_t & i) const
{
    return m_sensorEvents.get()[i].magnetic.x;
}

const float & MagneticField::Y(const size_t & i) const
{
    return m_sensorEvents.get()[i].magnetic.y;
}

const float & MagneticField::Z(const size_t & i) const
{
    return m_sensorEvents.get()[i].magnetic.z;
}

}