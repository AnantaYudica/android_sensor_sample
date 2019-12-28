//
// Created by Ananta Yudica on 28/12/2019.
//

#ifndef ANDROID_SENSOR_SAMPLE_SENSOREVENT_DEFAULT_H
#define ANDROID_SENSOR_SAMPLE_SENSOREVENT_DEFAULT_H

#include <android/sensor.h>
#include <memory>

namespace sensor_event
{

class Default
{
private:
    std::shared_ptr<ASensorEvent> m_sensorEvents;
    size_t  m_size;
public:
    Default();
    Default(std::shared_ptr<ASensorEvent> sensorEvents, const size_t & size);
public:
    ~Default();
public:
    Default(const Default & cpy);
    Default(Default && mov);
public:
    Default & operator=(const Default & cpy);
    Default & operator=(Default && mov);
public:
    size_t Size() const;
public:
    const int32_t& Version(const size_t & i = 0) const;
    const int32_t& Sensor(const size_t & i = 0) const;
    const int32_t& Type(const size_t & i = 0) const;
    const int32_t& Reserved0(const size_t & i = 0) const;
    const int64_t& Timestamp(const size_t & i = 0) const;
    const uint64_t (&Data(const size_t & i = 0) const)[8];
    const uint32_t& Flags(const size_t & i = 0) const;
    const int32_t (&Reserved1(const size_t & i = 0) const)[3];
public:
    operator bool() const;
    bool operator==(const Default & other) const;
    bool operator!=(const Default & other) const;
};

} //!sensor_event

#endif //ANDROID_SENSOR_SAMPLE_SENSOREVENT_DEFAULT_H
