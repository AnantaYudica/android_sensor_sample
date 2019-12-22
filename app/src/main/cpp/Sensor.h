//
// Created by Ananta Yudica on 21/12/2019.
//

#ifndef ANDROID_SENSOR_SAMPLE_SENSOR_H
#define ANDROID_SENSOR_SAMPLE_SENSOR_H

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
    ASensor * m_ptr;
public:
    Sensor(ASensor * ptr);
public:
    Sensor(const Sensor & cpy);
    Sensor(Sensor && mov);
public:
    ~Sensor();
private:
    void Init(ASensor * ptr);
    void InitType(ASensor * ptr);
    void InitMinDelay(ASensor * ptr);
    void InitResolution(ASensor * ptr);
    void InitName(ASensor * ptr);
    void InitVendor(ASensor * ptr);
public:
    Sensor & operator=(const Sensor &) = delete;
    Sensor & operator=(Sensor &&) = delete;
public:
    int Type() const;
    int MinDelay() const;
    float Resolution() const;
    const char * Name() const;
    const char * Vendor() const;
    ASensor * Pointer();
public:
    operator bool() const;
    bool operator==(const Sensor & sensor) const;
    bool operator!=(const Sensor & sensor) const;
};

#endif //ANDROID_SENSOR_SAMPLE_SENSOR_H