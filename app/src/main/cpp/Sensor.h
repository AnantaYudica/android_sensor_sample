//
// Created by Ananta Yudica on 21/12/2019.
//

#ifndef ANDROID_SENSOR_SAMPLE_SENSOR_H
#define ANDROID_SENSOR_SAMPLE_SENSOR_H

#include "Definition.h"
#include "sensor_event/Default.h"

#include <android/Sensor.h>

#include <memory>

class Sensor
{
private:
    static void __SetValueSharedString(std::shared_ptr<char> & val, const char * cstr,
        const size_t & size);
private:
    int m_type;
    int m_minDelay;
    float m_resolution;
    std::shared_ptr<char> m_name;
    std::shared_ptr<char> m_vendor;
    InfSensorType m_inf;
public:
    Sensor(InfSensorType inf);
public:
    Sensor(const Sensor & cpy);
    Sensor(Sensor && mov);
public:
     virtual ~Sensor();
private:
    void Init(InfSensorType inf);
    void InitType(InfSensorType inf);
    void InitMinDelay(InfSensorType inf);
    void InitResolution(InfSensorType inf);
    void InitName(InfSensorType inf);
    void InitVendor(InfSensorType inf);
public:
    virtual int Callback(sensor_event::Default events, std::size_t size) = 0;
public:
    Sensor & operator=(const Sensor &) = delete;
    Sensor & operator=(Sensor &&) = delete;
public:
    int Type() const;
    int MinDelay() const;
    float Resolution() const;
    const char * Name() const;
    const char * Vendor() const;
    InfSensorType Interface();
public:
    operator bool() const;
    bool operator==(const Sensor & sensor) const;
    bool operator!=(const Sensor & sensor) const;
};

#endif //ANDROID_SENSOR_SAMPLE_SENSOR_H
