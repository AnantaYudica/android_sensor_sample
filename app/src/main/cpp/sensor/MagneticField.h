//
// Created by Ananta Yudica on 12/01/2020.
//

#ifndef ANDROID_SENSOR_SAMPLE_SENSOR_MAGNETICFIELD_H
#define ANDROID_SENSOR_SAMPLE_SENSOR_MAGNETICFIELD_H

#include "../Sensor.h"
#include "../sensor_event/MagneticField.h"

#include <android/sensor.h>
#include <functional>

namespace sensor
{

class MagneticField : public Sensor
{

public:
    typedef int (CallbackFunType)(const Sensor &, const sensor_event::MagneticField &,
            const std::size_t &);
    typedef std::function<CallbackFunType> CallbackType;
private:
    static int __CallbackDefault(const Sensor &, const sensor_event::MagneticField &,
            const std::size_t &);
private:
    CallbackType m_callback;
public:
    MagneticField(ASensor const* ptr);
    MagneticField(ASensor const* ptr, CallbackType callback);
public:
    MagneticField(const MagneticField & cpy);
    MagneticField(MagneticField && mov);
public:
    ~MagneticField();
public:
    void SetCallback(CallbackType callback);
    CallbackType GetCallback();
public:
    MagneticField & operator=(const Sensor &) = delete;
    MagneticField & operator=(Sensor &&) = delete;
public:
    int Callback(sensor_event::Default events, std::size_t size);
};

} //!sensor


#endif //ANDROID_SENSOR_SAMPLE_SENSOR_MAGNETICFIELD_H
