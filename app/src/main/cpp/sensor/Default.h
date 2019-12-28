//
// Created by Ananta Yudica on 25/12/2019.
//

#ifndef ANDROID_SENSOR_SAMPLE_SENSOR_DEFAULT_H
#define ANDROID_SENSOR_SAMPLE_SENSOR_DEFAULT_H

#include "../Sensor.h"
#include "../sensor_event/Default.h"

#include <android/sensor.h>
#include <functional>

namespace sensor
{

class Default : public Sensor
{
public:
    typedef int (CallbackFunType)(const Sensor &, const sensor_event::Default &,
            const std::size_t &);
    typedef std::function<CallbackFunType> CallbackType;
private:
    static int __CallbackDefault(const Sensor &, const sensor_event::Default &,
             const std::size_t &);
private:
    CallbackType m_callback;
public:
    Default(ASensor const* ptr);
    Default(ASensor const* ptr, CallbackType callback);
public:
    Default(const Default & cpy);
    Default(Default && mov);
public:
    ~Default();
public:
    void SetCallback(CallbackType callback);
    CallbackType GetCallback();
public:
    Default & operator=(const Sensor &) = delete;
    Default & operator=(Sensor &&) = delete;
public:
    int Callback(sensor_event::Default events, std::size_t size);
};

} //!sensor


#endif //ANDROID_SENSOR_SAMPLE_SENSOR_DEFAULT_H
