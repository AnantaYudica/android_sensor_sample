//
// Created by Ananta Yudica on 04/01/2020.
//

#include "Default.h"

#include <functional>
#include <utility>

namespace bridge
{
namespace sensor
{
constexpr const char Default::ms_parameter_signature[];

constexpr size_t Default::ms_parameter_signature_size;

Default::Default(ASensor const* ptr) :
    ::sensor::Default(ptr)
{
    using namespace std::placeholders;
    SetCallback(std::bind(&Default::Callback, this, _1, _2, _3));
}

Default::~Default()
{}

Default::Default(const Default & cpy) :
    ::sensor::Default(cpy),
    bridge::Sensor(cpy)
{}

Default::Default(Default && mov) :
    ::sensor::Default(std::move(mov)),
    bridge::Sensor(std::move(mov))
{}

std::pair<const char *, size_t> Default::ParameterSignature()
{
    return {(const char *)ms_parameter_signature,
       ms_parameter_signature_size};
}

int Default::Callback(const ::Sensor & sensor, const sensor_event::Default & event,
     const std::size_t & size)
{
    if (!IsLink()) return 2;
    jsize size_data = sizeof(event.Data());
    jbyteArray bytes = Environment<jbyteArray, jsize>(&EnvironmentType::NewByteArray,
            std::move(size_data));
    jlong timestamp = 0;
    for (size_t i = 0; i < size; ++i)
    {
        Environment<void, jbyteArray, jsize, jsize, const jbyte*>(
                &EnvironmentType::SetByteArrayRegion, std::move(bytes), 0,
                std::move(size_data), (jbyte*)(&event.Data(i)));
        timestamp = event.Timestamp(i);
        auto res = Call(bytes, timestamp);
        if (res < 0) return res;
    }
    return 1;
}

} //!sensor

} //!bridge
