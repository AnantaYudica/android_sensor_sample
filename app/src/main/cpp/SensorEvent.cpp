//
// Created by Ananta Yudica on 27/12/2019.
//

#include "SensorEvent.h"
#include "Log.h"
#include "make/SensorEvent.h"

#include <chrono>
#include <memory>

constexpr const int SensorEvent::OK;
constexpr const int SensorEvent::ERROR_NO_SENSOR;
constexpr const int SensorEvent::ERROR_NO_SENSORMANAGER;
constexpr const int SensorEvent::ERROR_PREPARE_LOOPER;
constexpr const int SensorEvent::ERROR_CREATE_EVENTQUEUE;
constexpr const int SensorEvent::ERROR_INIT_THREAD;
constexpr const int SensorEvent::ERROR_ENABLE_SENSOR;
constexpr const int SensorEvent::ERROR_DISABLE_SENSOR;
constexpr const int SensorEvent::ERROR_SET_EVENT_RATE;
constexpr const int SensorEvent::ERROR_HAS_EVENTS;
constexpr const int SensorEvent::ERROR_GET_EVENTS;
constexpr const int SensorEvent::ERROR_CALLBACK;
constexpr const int SensorEvent::ERROR_MAKE_SENSOREVENT;

SensorEvent::SensorEvent(InfSensorManagerType infSensorManager, Sensor * pSensor) :
    m_delay(-1),
    m_error(OK),
    m_flag(0),
    m_queueSize(10),
    m_sensormanager(infSensorManager),
    m_sensor(pSensor),
    m_eventQueue(nullptr),
    m_eventData(nullptr),
    m_looper(nullptr),
    m_thread(nullptr),
    m_data(nullptr)
{
    LOG_DEBUG("SensorEvent", "Constructor(...)");
    Init();
}

SensorEvent::SensorEvent(InfSensorManagerType infSensorManager, Sensor * pSensor,
    const int& delay) :
        m_delay(-1),
        m_error(OK),
        m_flag(0),
        m_queueSize(10),
        m_sensormanager(infSensorManager),
        m_sensor(pSensor),
        m_eventQueue(nullptr),
        m_eventData(nullptr),
        m_looper(nullptr),
        m_thread(nullptr),
        m_data(nullptr)
{
    LOG_DEBUG("SensorEvent", "Constructor(...)");
    Init(delay);
}

SensorEvent::SensorEvent(const size_t & queue_size, InfSensorManagerType infSensorManager,
    Sensor * pSensor) :
        m_delay(-1),
        m_error(OK),
        m_flag(0),
        m_queueSize(queue_size == 0 ? 1 : queue_size),
        m_sensormanager(infSensorManager),
        m_sensor(pSensor),
        m_eventQueue(nullptr),
        m_eventData(nullptr),
        m_looper(nullptr),
        m_thread(nullptr),
        m_data(nullptr)
{
    LOG_DEBUG("SensorEvent", "Constructor(...)");
    Init();
}

SensorEvent::SensorEvent(const size_t & queue_size, InfSensorManagerType infSensorManager,
    Sensor * pSensor, const int& delay) :
        m_delay(-1),
        m_error(OK),
        m_flag(0),
        m_queueSize(queue_size == 0 ? 1 : queue_size),
        m_sensormanager(infSensorManager),
        m_sensor(pSensor),
        m_eventQueue(nullptr),
        m_eventData(nullptr),
        m_looper(nullptr),
        m_thread(nullptr),
        m_data(nullptr)
{
    LOG_DEBUG("SensorEvent", "Constructor(...)");
    Init(delay);
}

SensorEvent::~SensorEvent()
{
    LOG_DEBUG("SensorEvent", "Destructor(...)");
    Stop();
    m_error = OK;
    m_delay = -1;
    m_queueSize = 0;
    m_flag.store(0, std::memory_order_relaxed);
    m_sensormanager = nullptr;
    m_sensor = nullptr;
}

int SensorEvent::Init(const int& delay)
{
    LOG_DEBUG("SensorEvent", "Init(...)");
    if (!m_sensor) return __SetError<int>(this, m_error, ERROR_NO_SENSOR, -1);
    else m_delay = delay >= m_sensor->MinDelay() ? delay : m_sensor->MinDelay();
    if (!m_sensormanager) return __SetError<int>(this, m_error, ERROR_NO_SENSORMANAGER, -2);
    return 0;
}

int SensorEvent::InitThread()
{
    LOG_DEBUG("SensorEvent", "InitThread(...)");
    m_thread = new std::thread(&SensorEvent::Run, this);
    LOG_DEBUG("SensorEvent", "thread : %p", (void*)m_thread);
    if (!m_thread)
        return __SetError<int>(this, m_error, ERROR_INIT_THREAD, -1);
    return 1;
}

int SensorEvent::InitLooper()
{
    LOG_DEBUG("SensorEvent", "InitLooper(...)");
    m_looper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);
    LOG_DEBUG("SensorEvent", "looper : %p", (void*)m_looper);
    if (!m_looper)
        return __SetError<int>(this, m_error, ERROR_PREPARE_LOOPER, -1);
    ALooper_acquire(m_looper);
    return 1;
}

int SensorEvent::InitEventQueue()
{
    LOG_DEBUG("SensorEvent", "InitEventQueue(...)");
    sensor::manager::CreateEventQueue(m_sensormanager, m_looper,
            0, nullptr, m_data, &m_eventQueue);
    LOG_DEBUG("SensorEvent", "eventQueue : %p", (void*)m_eventQueue);
    if (!m_eventQueue)
        return __SetError<int>(this, m_error, ERROR_CREATE_EVENTQUEUE, -1);
    return 1;
}

int SensorEvent::InitEventData()
{
    LOG_DEBUG("SensorEvent", "InitEventData(...)");
    if (!make::SensorEvent(m_sensor->Type(), m_eventData))
        return __SetError<int>(this, m_error, ERROR_MAKE_SENSOREVENT, -1);
    return 1;
}

int SensorEvent::InitEnableSensor()
{
    LOG_DEBUG("SensorEvent", "InitEnableSensor(...)");

    if (sensor::event::queue::EnableSensor(m_eventQueue, m_sensor->Interface()) != 0)
        return __SetError<int>(this, m_error, ERROR_ENABLE_SENSOR, -1);
    return 0;
}

int SensorEvent::InitDisableSensor()
{
    LOG_DEBUG("SensorEvent", "InitDisableSensor(...)");
    if (sensor::event::queue::DisableSensor(m_eventQueue, m_sensor->Interface()) != 0)
        return __SetError<int>(this, m_error, ERROR_DISABLE_SENSOR, -1);
    return 0;
}

int SensorEvent::InitEventRate()
{
    LOG_DEBUG("SensorEvent", "InitEventRate(...)");
    if  (sensor::event::queue::SetEventRate(m_eventQueue, m_sensor->Interface(), m_delay) != 0)
        return __SetError<int>(this, m_error, ERROR_SET_EVENT_RATE, -1);
    LOG_DEBUG("SensorEvent", "set delay %d microseconds", m_delay);
    return 0;
}

void SensorEvent::InitEnable()
{
    LOG_DEBUG("SensorEvent", "InitEnable(...)");
    if (!InitEventQueue()) return;
    if (!InitEnableSensor() || !InitEventRate())
    {
        ReleaseEventQueue();
        return;
    }
    SetEnable();
}

void SensorEvent::InitDisable()
{
    LOG_DEBUG("SensorEvent", "InitDisable(...)");
    InitDisableSensor();
    ReleaseEventQueue();
    SetDisable();
}

void SensorEvent::InitPause()
{
    LOG_DEBUG("SensorEvent", "InitPause(...)");
    if (IsEnable()) InitDisableSensor();
    SetPause();
}

void SensorEvent::InitResume()
{
    LOG_DEBUG("SensorEvent", "InitResume(...)");
    if (IsEnable()) InitEnableSensor();
    SetResume();
}

void SensorEvent::ReleaseThread()
{
    LOG_DEBUG("SensorEvent", "ReleaseThread(...)");
    if (m_thread)
    {
        m_thread->join();
        delete m_thread;
        m_thread = nullptr;
    }
}

void SensorEvent::ReleaseLooper()
{
    LOG_DEBUG("SensorEvent", "ReleaseLooper(...)");
    if (!m_looper) return;
    ALooper_release(m_looper);
    m_looper = nullptr;
}

void SensorEvent::ReleaseEventQueue()
{
    LOG_DEBUG("SensorEvent", "ReleaseEventQueue(...)");
    if (!m_eventQueue) return;
    sensor::manager::DestroyEventQueue(m_sensormanager, m_eventQueue);
    m_eventQueue = nullptr;
    m_data = nullptr;
}

void SensorEvent::ReleaseEventData()
{
    LOG_DEBUG("SensorEvent", "ReleaseEventData(...)");
    if (!m_eventData) return;
    delete m_eventData;
    m_eventData = nullptr;
}

void SensorEvent::Run()
{
    LOG_DEBUG("SensorEvent", "Run(...)");
    if (!InitLooper() || !InitEventData()) return;
    if (!IsEnable() && IsPrepareEnable())
        InitEnable();
    InfSensorEventType sensor_events = sensor::AllocateEvents(m_queueSize);
    SetStart();
    while(!IsError() && !IsRun())
    {
        const auto is_prepare_pause = IsPreparePause();
        const auto is_pause = IsPause();
        if (is_prepare_pause != is_pause)
        {
            if (is_prepare_pause) InitPause();
            else InitResume();
        }
        if (is_pause)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(700));
            continue;
        }
        if (!IsEnable() || !IsPrepareEnable()) continue;
        auto has_events = sensor::event::queue::HasEvents(m_eventQueue);
        if(has_events < 0)
        {
            __SetError<void>(this, m_error, ERROR_HAS_EVENTS);
            continue;
        }
        else if (has_events == 0) continue;
        const auto size = sensor::event::queue::GetEvents(m_eventQueue,
                sensor_events, m_queueSize);
        if (size < 0)
        {
            __SetError<void>(this, m_error, ERROR_GET_EVENTS);
            continue;
        }
        m_eventData->SetEvents(sensor_events, m_queueSize);
        if (m_sensor->Callback(*m_eventData, (size_t)size) < 0)
        {
            __SetError<void>(this, m_error, ERROR_CALLBACK);
            continue;
        }
    }
    SetStop();
    if (IsEnable()) InitDisable();
    ReleaseEventData();
    ReleaseLooper();
}

int SensorEvent::Delay() const
{
    return m_delay;
}

void SensorEvent::Delay(const int & val)
{
    LOG_DEBUG("SensorEvent", "Delay(...)");
    if (!m_sensor) return;
    if (val >= m_sensor->MinDelay())
        m_delay = val;
    if (IsRun() && IsEnable()) InitEventRate();
    LOG_DEBUG("SensorEvent", "delya : %d", m_delay);
}

int SensorEvent::LastErrorCode() const
{
    return m_error;
}

void SensorEvent::Enable()
{
    LOG_DEBUG("SensorEvent", "Enable(...)");
    if (IsPrepareEnable()) return;
    SetPrepareEnable();
    if (IsRun()) InitEnable();
}

void SensorEvent::Disable()
{
    LOG_DEBUG("SensorEvent", "Disable(...)");
    if (!IsPrepareEnable()) return;
    SetPrepareDisable();
    if (IsRun()) InitDisable();
}

void SensorEvent::Pause()
{
    LOG_DEBUG("SensorEvent", "Pause(...)");
    if (IsPreparePause()) return;
    SetPreparePause();
}

void SensorEvent::Resume()
{
    LOG_DEBUG("SensorEvent", "Resume(...)");
    if (!IsPreparePause()) return;
    SetPrepareResume();
}

void SensorEvent::Start()
{
    LOG_DEBUG("SensorEvent", "Start(...)");
    if (IsRun() || m_thread) return;
    if (!InitThread()) SetStop();
}

void SensorEvent::Stop()
{
    LOG_DEBUG("SensorEvent", "Stop(...)");
    if (!IsRun()) return;
    SetStop();
    ReleaseThread();
}

void SensorEvent::SetError()
{
    m_flag.fetch_or(FLAG_ERROR_SENSOR, std::memory_order_release);
}

void SensorEvent::SetPrepareEnable()
{
    m_flag.fetch_or(FLAG_PREPARE_ENABLE_SENSOR, std::memory_order_release);
}

void SensorEvent::SetPrepareDisable()
{
    m_flag.fetch_and(~FLAG_PREPARE_ENABLE_SENSOR, std::memory_order_release);
}

void SensorEvent::SetEnable()
{
    m_flag.fetch_or(FLAG_ENABLE_SENSOR, std::memory_order_release);
}

void SensorEvent::SetDisable()
{
    m_flag.fetch_and(~FLAG_ENABLE_SENSOR, std::memory_order_release);
}

void SensorEvent::SetPreparePause()
{
    m_flag.fetch_or(FLAG_PREPARE_PAUSE_SENSOR, std::memory_order_release);
}

void SensorEvent::SetPrepareResume()
{
    m_flag.fetch_and(~FLAG_PREPARE_PAUSE_SENSOR, std::memory_order_release);
}

void SensorEvent::SetPause()
{
    m_flag.fetch_or(FLAG_PAUSE_SENSOR, std::memory_order_release);
}

void SensorEvent::SetResume()
{
    m_flag.fetch_and(~FLAG_PAUSE_SENSOR, std::memory_order_release);
}

void SensorEvent::SetStart()
{
    m_flag.fetch_or(FLAG_RUN_SENSOR, std::memory_order_release);
}

void SensorEvent::SetStop()
{
    m_flag.fetch_and(~FLAG_RUN_SENSOR, std::memory_order_release);
}

bool SensorEvent::IsPrepareEnable() const
{
    return m_flag.load(std::memory_order_consume) &
           FLAG_PREPARE_ENABLE_SENSOR;
}

bool SensorEvent::IsPreparePause() const
{
    return m_flag.load(std::memory_order_consume) &
           FLAG_PREPARE_PAUSE_SENSOR;
}

bool SensorEvent::IsError() const
{
    return m_flag.load(std::memory_order_consume) <
        std::int8_t(0);
}

bool SensorEvent::IsEnable() const
{
    return m_flag.load(std::memory_order_consume) &
        FLAG_ENABLE_SENSOR;
}

bool SensorEvent::IsPause() const
{
    return m_flag.load(std::memory_order_consume) &
        FLAG_PAUSE_SENSOR;
}

bool SensorEvent::IsRun() const
{
    return m_flag.load(std::memory_order_consume) &
        FLAG_RUN_SENSOR;
}

