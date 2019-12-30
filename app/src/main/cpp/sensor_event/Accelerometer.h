//
// Created by Ananta Yudica on 29/12/2019.
//

#ifndef ANDROID_SENSOR_SAMPLE_SENSOREVENT_ACCELEROMETER_H
#define ANDROID_SENSOR_SAMPLE_SENSOREVENT_ACCELEROMETER_H

#include "Default.h"

#include <memory>
#include <android/sensor.h>

namespace sensor_event
{

class Accelerometer : public Default
{
public:
    Accelerometer();
    Accelerometer(std::shared_ptr<ASensorEvent> sensorEvents, const size_t & size);
public:
    ~Accelerometer();
public:
    Accelerometer(const Accelerometer & cpy);
    Accelerometer(Accelerometer && mov);
    Accelerometer(const Default & cpy);
    Accelerometer(Default && mov);
public:
    Accelerometer & operator=(const Accelerometer & cpy);
    Accelerometer & operator=(Accelerometer && mov);
    Accelerometer & operator=(const Default & cpy);
    Accelerometer & operator=(Default && mov);
public:
    const float & X(const size_t & i = 0) const;
    const float & Y(const size_t & i = 0) const;
    const float & Z(const size_t & i = 0) const;
};

} //!sensor_event

#endif //ANDROID_SENSOR_SAMPLE_SENSOREVENT_ACCELEROMETER_H
