//
// Created by Ananta Yudica on 12/01/2020.
//

#include "MagneticField.h"

#include <functional>
#include <utility>

namespace bridge
{
namespace sensor
{

constexpr const char MagneticField::ms_parameter_signature[];
constexpr size_t MagneticField::ms_parameter_signature_size;

MagneticField::MagneticField(ASensor const* ptr) :
    ::sensor::MagneticField(ptr)
{
    using namespace std::placeholders;
    SetCallback(std::bind(&MagneticField::Callback, this, _1, _2, _3));
}

MagneticField::~MagneticField()
{}

MagneticField::MagneticField(const MagneticField & cpy) :
    ::sensor::MagneticField(cpy),
    bridge::Sensor(cpy)
{}

MagneticField::MagneticField(MagneticField && mov) :
    ::sensor::MagneticField(std::move(mov)),
    bridge::Sensor(std::move(mov))
{}

std::pair<const char *, size_t> MagneticField::ParameterSignature()
{
    return {(const char *)ms_parameter_signature, ms_parameter_signature_size};
}

int MagneticField::Callback(const ::Sensor & sensor,
    const sensor_event::MagneticField & event, const std::size_t & size)
{
    if (!IsLink()) return 2;
    jfloat x = 0,y = 0, z = 0;
    jlong timestamp = 0;
    for (size_t i = 0; i < size; ++i)
    {
        x = event.X(i);
        y = event.Y(i);
        z = event.Z(i);
        timestamp = event.Timestamp(i);
        auto res = Call(x, y, z, timestamp);
        if (res < 0) return res;
    }
    return 1;
}

} //!sensor

} //!bridge
