//
// Created by Ananta Yudica on 04/01/2020.
//

#ifndef ANDROID_SENSOR_SAMPLE_BRIDGE_SENSOR_DEFAULT_H
#define ANDROID_SENSOR_SAMPLE_BRIDGE_SENSOR_DEFAULT_H

#include "../Sensor.h"
#include "../../sensor/Default.h"

#include <android/sensor.h>

namespace bridge
{
namespace sensor
{

class Default :
    public ::sensor::Default,
    public bridge::Sensor
{
private:
    static constexpr const char ms_parameter_signature[] = "[CJ";
    static constexpr size_t ms_parameter_signature_size =
        sizeof(ms_parameter_signature);
public:
    Default(ASensor const* ptr);
public:
    ~Default();
public:
    Default(const Default & cpy);
    Default(Default && mov);
public:
    Default & operator=(const Default &) = delete;
    Default & operator=(Default &&) = delete;
public:
    std::pair<const char *, size_t> ParameterSignature();
    int Callback(const ::Sensor & sensor, const sensor_event::Default & event,
            const std::size_t & size);
};

} //!sensor

} //!bridge

#endif //ANDROID_SENSOR_SAMPLE_BRIDGE_SENSOR_DEFAULT_H
