//
// Created by Ananta Yudica on 06/01/2020.
//

#ifndef ANDROID_SENSOR_SAMPLE_BRIDGE_SENSORMANAGER_H
#define ANDROID_SENSOR_SAMPLE_BRIDGE_SENSORMANAGER_H

#include "../SensorManager.h"
#include "../Definition.h"

namespace bridge
{

class SensorManager : public ::SensorManager
{
public:
    SensorManager();
public:
    ~SensorManager();
protected:
    int InitSensor(const int & type, ::Sensor * & sensor, InfSensorType infsensor);
};

} //!bridge

#endif //ANDROID_SENSOR_SAMPLE_BRIDGE_SENSORMANAGER_H
