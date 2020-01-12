//
// Created by Ananta Yudica on 12/01/2020.
//

#ifndef ANDROID_SENSOR_SAMPLE_SENSOREVENT_GYROSCOPE_H
#define ANDROID_SENSOR_SAMPLE_SENSOREVENT_GYROSCOPE_H

#include "Default.h"

#include <memory>
#include <android/sensor.h>

namespace sensor_event
{

class Gyroscope : public Default
{
public:
    Gyroscope();
    Gyroscope(std::shared_ptr<ASensorEvent> sensorEvents, const size_t & size);
public:
    ~Gyroscope();
public:
    Gyroscope(const Gyroscope & cpy);
    Gyroscope(Gyroscope && mov);
    Gyroscope(const Default & cpy);
    Gyroscope(Default && mov);
public:
    Gyroscope & operator=(const Gyroscope & cpy);
    Gyroscope & operator=(Gyroscope && mov);
    Gyroscope & operator=(const Default & cpy);
    Gyroscope & operator=(Default && mov);
public:
    const float & X(const size_t & i = 0) const;
    const float & Y(const size_t & i = 0) const;
    const float & Z(const size_t & i = 0) const;
};

} //!sensor_event

#endif //ANDROID_SENSOR_SAMPLE_SENSOREVENT_GYROSCOPE_H
