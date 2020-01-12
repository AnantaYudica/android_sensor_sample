//
// Created by Ananta Yudica on 12/01/2020.
//

#ifndef ANDROID_SENSOR_SAMPLE_BRIDGE_SENSOR_MAGNETICFIELD_H
#define ANDROID_SENSOR_SAMPLE_BRIDGE_SENSOR_MAGNETICFIELD_H

#include "../../sensor/MagneticField.h"
#include "../Sensor.h"

#include <android/sensor.h>

namespace bridge
{
namespace sensor
{

class MagneticField :
    public ::sensor::MagneticField,
    public bridge::Sensor
{
private:
    static constexpr const char ms_parameter_signature[] = "FFFJ";
    static constexpr size_t ms_parameter_signature_size =
        sizeof(ms_parameter_signature);
public:
    MagneticField(ASensor const* ptr);
public:
    ~MagneticField();
public:
    MagneticField(const MagneticField & cpy);
    MagneticField(MagneticField && mov);
public:
    MagneticField & operator=(const MagneticField &) = delete;
    MagneticField & operator=(MagneticField &&) = delete;
public:
    std::pair<const char *, size_t> ParameterSignature();
    int Callback(const ::Sensor & sensor, const sensor_event::MagneticField & event,
         const std::size_t & size);
};

} //!sensor

} //!bridge


#endif //ANDROID_SENSOR_SAMPLE_BRIDGE_SENSOR_MAGNETICFIELD_H
