//
// Created by Ananta Yudica on 12/01/2020.
//

#ifndef ANDROID_SENSOR_SAMPLE_BRIDGE_SENSOR_GYROSCOPE_H
#define ANDROID_SENSOR_SAMPLE_BRIDGE_SENSOR_GYROSCOPE_H

#include "../../sensor/Gyroscope.h"
#include "../Sensor.h"

#include <android/sensor.h>

namespace bridge
{
namespace sensor
{

class Gyroscope :
    public ::sensor::Gyroscope,
    public bridge::Sensor
{
private:
    static constexpr const char ms_parameter_signature[] = "FFFJ";
    static constexpr size_t ms_parameter_signature_size =
        sizeof(ms_parameter_signature);
public:
    Gyroscope(ASensor const* ptr);
public:
    ~Gyroscope();
public:
    Gyroscope(const Gyroscope & cpy);
    Gyroscope(Gyroscope && mov);
public:
    Gyroscope & operator=(const Gyroscope &) = delete;
    Gyroscope & operator=(Gyroscope &&) = delete;
public:
    std::pair<const char *, size_t> ParameterSignature();
    int Callback(const ::Sensor & sensor, const sensor_event::Gyroscope & event,
         const std::size_t & size);
};

} //!sensor

} //!bridge

#endif //ANDROID_SENSOR_SAMPLE_BRIDGE_SENSOR_GYROSCOPE_H
