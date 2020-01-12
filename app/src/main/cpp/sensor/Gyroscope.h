//
// Created by Ananta Yudica on 12/01/2020.
//

#ifndef ANDROID_SENSOR_SAMPLE_SENSOR_GYROSCOPE_H
#define ANDROID_SENSOR_SAMPLE_SENSOR_GYROSCOPE_H

#include "../Sensor.h"
#include "../sensor_event/Gyroscope.h"

#include <android/sensor.h>
#include <functional>

namespace sensor
{

class Gyroscope : public Sensor
{
public:
    typedef int (CallbackFunType)(const Sensor &, const sensor_event::Gyroscope &,
            const std::size_t &);
    typedef std::function<CallbackFunType> CallbackType;
private:
    static int __CallbackDefault(const Sensor &, const sensor_event::Gyroscope &,
            const std::size_t &);
private:
    CallbackType m_callback;
public:
    Gyroscope(ASensor const* ptr);
    Gyroscope(ASensor const* ptr, CallbackType callback);
public:
    Gyroscope(const Gyroscope & cpy);
    Gyroscope(Gyroscope && mov);
public:
    ~Gyroscope();
public:
    void SetCallback(CallbackType callback);
    CallbackType GetCallback();
public:
    Gyroscope & operator=(const Sensor &) = delete;
    Gyroscope & operator=(Sensor &&) = delete;
public:
    int Callback(sensor_event::Default events, std::size_t size);
};

} //!sensor


#endif //ANDROID_SENSOR_SAMPLE_SENSOR_GYROSCOPE_H
