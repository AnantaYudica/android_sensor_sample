//
// Created by Ananta Yudica on 04/01/2020.
//

#ifndef ANDROID_SENSOR_SAMPLE_BRIDGE_SENSOR_ACCLEROMETER_H
#define ANDROID_SENSOR_SAMPLE_BRIDGE_SENSOR_ACCLEROMETER_H

#include "../../sensor/Accelerometer.h"
#include "../Sensor.h"

#include <android/sensor.h>

namespace bridge
{
namespace sensor
{

class Accelerometer :
    public ::sensor::Accelerometer,
    public bridge::Sensor
{
private:
    static constexpr const char ms_parameter_signature[] = "FFFJ";
    static constexpr size_t ms_parameter_signature_size =
        sizeof(ms_parameter_signature);
public:
    Accelerometer(ASensor const* ptr);
public:
    ~Accelerometer();
public:
    Accelerometer(const Accelerometer & cpy);
    Accelerometer(Accelerometer && mov);
public:
    Accelerometer & operator=(const Accelerometer &) = delete;
    Accelerometer & operator=(Accelerometer &&) = delete;
public:
    std::pair<const char *, size_t> ParameterSignature();
    int Callback(const ::Sensor & sensor, const sensor_event::Accelerometer & event,
         const std::size_t & size);
};

} //!sensor

} //!bridge


#endif //ANDROID_SENSOR_SAMPLE_BRIDGE_SENSOR_ACCLEROMETER_H
