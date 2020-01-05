//
// Created by Ananta Yudica on 05/01/2020.
//

#ifndef ANDROID_SENSOR_SAMPLE_MAKE_SENSOREVENT_H
#define ANDROID_SENSOR_SAMPLE_MAKE_SENSOREVENT_H

#include "../Definition.h"
#include "../sensor_event/Default.h"
#include "../sensor_event/Accelerometer.h"
#include <utility>
#include <type_traits>

namespace make
{

template<typename TBase = sensor_event::Default, typename ... TArgs>
typename std::enable_if<std::is_pointer<TBase>::value, int>::type
SensorEvent(const int & type, TBase & out, TArgs && ... args)
{
    if (out != nullptr) return 2;
    if (type == static_cast<int>(sensor::Type::invalid)) return -1;
    if (type == static_cast<int>(sensor::Type::accelerometer))
        out = new sensor_event::Accelerometer(std::forward<TArgs>(args)...);
    else
        out = new sensor_event::Default(std::forward<TArgs>(args)...);
    return 1;
}

template<typename TBase = sensor_event::Default, typename ... TArgs>
typename std::enable_if<!std::is_pointer<TBase>::value, int>::type
SensorEvent(const int & type, TBase & out, TArgs && ... args)
{
    if (type == static_cast<int>(sensor::Type::invalid)) return -1;
    if (type == static_cast<int>(sensor::Type::accelerometer))
        out = sensor_event::Accelerometer(std::forward<TArgs>(args)...);
    else
        out = sensor_event::Default(std::forward<TArgs>(args)...);
    return 1;
}

} //!defn

#endif //ANDROID_SENSOR_SAMPLE_MAKE_SENSOREVENT_H
