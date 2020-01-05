//
// Created by Ananta Yudica on 25/12/2019.
//

#ifndef ANDROID_SENSOR_SAMPLE_SENSOR_ACCELEROMETER_H
#define ANDROID_SENSOR_SAMPLE_SENSOR_ACCELEROMETER_H

#include "../Sensor.h"
#include "../sensor_event/Accelerometer.h"

#include <android/sensor.h>
#include <functional>

namespace sensor
{

class Accelerometer : public Sensor
{
public:
    typedef int (CallbackFunType)(const Sensor &, const sensor_event::Accelerometer &,
          const std::size_t &);
    typedef std::function<CallbackFunType> CallbackType;
private:
    static int __CallbackDefault(const Sensor &, const sensor_event::Accelerometer &,
         const std::size_t &);
private:
    CallbackType m_callback;
public:
    Accelerometer(ASensor const* ptr);
    Accelerometer(ASensor const* ptr, CallbackType callback);
public:
    Accelerometer(const Accelerometer & cpy);
    Accelerometer(Accelerometer && mov);
public:
    ~Accelerometer();
public:
    void SetCallback(CallbackType callback);
    CallbackType GetCallback();
public:
    Accelerometer & operator=(const Sensor &) = delete;
    Accelerometer & operator=(Sensor &&) = delete;
public:
    int Callback(sensor_event::Default events, std::size_t size);
};

} //!sensor


#endif //ANDROID_SENSOR_SAMPLE_SENSOR_ACCELEROMETER_H
