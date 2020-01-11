//
// Created by Ananta Yudica on 11/01/2020.
//

#ifndef ANDROID_SENSOR_SAMPLE_SENSOREVENT_MAGNETICFIELD_H
#define ANDROID_SENSOR_SAMPLE_SENSOREVENT_MAGNETICFIELD_H

#include "Default.h"

#include <memory>
#include <android/sensor.h>

namespace sensor_event
{

class MagneticField : public Default
{
public:
    MagneticField();
    MagneticField(std::shared_ptr<ASensorEvent> sensorEvents, const size_t & size);
public:
    ~MagneticField();
public:
    MagneticField(const MagneticField & cpy);
    MagneticField(MagneticField && mov);
    MagneticField(const Default & cpy);
    MagneticField(Default && mov);
public:
    MagneticField & operator=(const MagneticField & cpy);
    MagneticField & operator=(MagneticField && mov);
    MagneticField & operator=(const Default & cpy);
    MagneticField & operator=(Default && mov);
public:
    const float & X(const size_t & i = 0) const;
    const float & Y(const size_t & i = 0) const;
    const float & Z(const size_t & i = 0) const;
};

} //!sensor_event

#endif //ANDROID_SENSOR_SAMPLE_SENSOREVENT_MAGNETICFIELD_H
