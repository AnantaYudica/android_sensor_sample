//
// Created by Ananta Yudica on 04/01/2020.
//

#include "Accelerometer.h"

#include <functional>
#include <utility>

namespace bridge
{
namespace sensor
{

constexpr const char Accelerometer::ms_parameter_signature[];

constexpr size_t Accelerometer::ms_parameter_signature_size;

Accelerometer::Accelerometer(ASensor const* ptr) :
    ::sensor::Accelerometer(ptr)
{
    using namespace std::placeholders;
    SetCallback(std::bind(&Accelerometer::Callback, this, _1, _2, _3));
}

Accelerometer::~Accelerometer()
{}

Accelerometer::Accelerometer(const Accelerometer & cpy) :
    ::sensor::Accelerometer(cpy),
    bridge::Sensor(cpy)
{}

Accelerometer::Accelerometer(Accelerometer && mov) :
    ::sensor::Accelerometer(std::move(mov)),
    bridge::Sensor(std::move(mov))
{}

std::pair<const char *, size_t> Accelerometer::ParameterSignature()
{
    return {(const char *)ms_parameter_signature, ms_parameter_signature_size};
}

int Accelerometer::Callback(const ::Sensor & sensor, const sensor_event::Accelerometer & event,
     const std::size_t & size)
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

