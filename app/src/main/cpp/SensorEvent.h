//
// Created by Ananta Yudica on 27/12/2019.
//

#ifndef ANDROID_SENSOR_SAMPLE_SENSOREVENT_H
#define ANDROID_SENSOR_SAMPLE_SENSOREVENT_H

#include <android/sensor.h>
#include <android/looper.h>
#include <thread>
#include <atomic>
#include <cstdint>
#include <type_traits>

#include "Sensor.h"

class SensorEvent
{
private:
    static constexpr const std::int8_t FLAG_PREPARE_ENABLE_SENSOR = 0x01;
    static constexpr const std::int8_t FLAG_ENABLE_SENSOR = 0x02;
    static constexpr const std::int8_t FLAG_PREPARE_PAUSE_SENSOR = 0x04;
    static constexpr const std::int8_t FLAG_PAUSE_SENSOR = 0x08;
    static constexpr const std::int8_t FLAG_RUN_SENSOR = 0x10;
    static constexpr const std::int8_t FLAG_ERROR_SENSOR = 0x80;
public:
    static constexpr const int OK = 0x00;
    static constexpr const int ERROR_NO_SENSOR = 0x01;
    static constexpr const int ERROR_NO_SENSORMANAGER = 0x02;
    static constexpr const int ERROR_PREPARE_LOOPER = 0x03;
    static constexpr const int ERROR_CREATE_EVENTQUEUE = 0x04;
    static constexpr const int ERROR_INIT_THREAD = 0x05;
    static constexpr const int ERROR_ENABLE_SENSOR = 0x06;
    static constexpr const int ERROR_DISABLE_SENSOR = 0x07;
    static constexpr const int ERROR_SET_EVENT_RATE = 0x08;
    static constexpr const int ERROR_HAS_EVENTS = 0x09;
    static constexpr const int ERROR_GET_EVENTS = 0x0A;
private:
    template<typename TRet>
    static typename std::enable_if<std::is_same<TRet, void>::value, TRet>::type
    __SetError(SensorEvent * pThis, int & err, const int & code);
    template<typename TRet>
    static typename std::enable_if<!std::is_same<TRet, void>::value, TRet>::type
    __SetError(SensorEvent * pThis, int & err, const int & code, const TRet & ret);
private:
    int m_delay;
    int m_error;
    size_t m_queueSize;
    std::atomic<std::int8_t> m_flag;
    ASensorManager * m_sensormanager;
    Sensor * m_sensor;
    ASensorEventQueue * m_eventQueue;
    ALooper * m_looper;
    std::thread * m_thread;
    void * m_data;
public:
    SensorEvent(ASensorManager * pSensorManager, Sensor * pSensor);
    SensorEvent(ASensorManager * pSensorManager, Sensor * pSensor,
            const int& delay);
    SensorEvent(const size_t & queue_size, ASensorManager * pSensorManager,
            Sensor * pSensor);
    SensorEvent(const size_t & queue_size, ASensorManager * pSensorManager,
            Sensor * pSensor, const int& delay);
    ~SensorEvent();
public:
    SensorEvent(const SensorEvent &) = delete;
    SensorEvent(SensorEvent &&) = delete;
private:
    int Init(const int& delay = -1);
    int InitThread();
    int InitLooper();
    int InitEventQueue();
    int InitEnableSensor();
    int InitDisableSensor();
    int InitEventRate();
    void InitEnable();
    void InitDisable();
    void InitPause();
    void InitResume();
private:
    void ReleaseThread();
    void ReleaseLooper();
    void ReleaseEventQueue();
private:
    void Run();
public:
    int Delay() const;
    void Delay(const int & val);
public:
    int LastErrorCode() const;
public:
    void Enable();
    void Disable();
    void Pause();
    void Resume();
    void Start();
    void Stop();
private:
    void SetError();
    void SetPrepareEnable();
    void SetPrepareDisable();
    void SetEnable();
    void SetDisable();
    void SetPreparePause();
    void SetPrepareResume();
    void SetPause();
    void SetResume();
    void SetStart();
    void SetStop();
private:
    bool IsPrepareEnable() const;
    bool IsPreparePause() const;
public:
    bool IsError() const;
    bool IsEnable() const;
    bool IsPause() const;
    bool IsRun() const;
public:
    SensorEvent & operator=(const SensorEvent &) = delete;
    SensorEvent & operator=(SensorEvent &&) = delete;
};

template<typename TRet>
typename std::enable_if<std::is_same<TRet, void>::value, TRet>::type
SensorEvent::__SetError(SensorEvent * pThis, int & err, const int & code)
{
    err = code;
    pThis->SetError();
}

template<typename TRet>
typename std::enable_if<!std::is_same<TRet, void>::value, TRet>::type
SensorEvent::__SetError(SensorEvent * pThis, int & err, const int & code, const TRet & ret)
{
    err = code;
    pThis->SetError();
    return ret;
}

#endif //ANDROID_SENSOR_SAMPLE_SENSOREVENT_H
