cmake_minimum_required(VERSION 3.4.1)

add_compile_options(-std=c++11)

add_library(Bridge SHARED ../src/main/cpp/Bridge.cpp
        ../src/main/cpp/jni/SensorManager.cpp
        ../src/main/cpp/jni/Sensor.cpp
        ../src/main/cpp/jni/sensor/Default.cpp
        ../src/main/cpp/jni/sensor/Accelerometer.cpp
        ../src/main/cpp/jni/sensor/MagneticField.cpp
        ../src/main/cpp/jni/sensor/Gyroscope.cpp
        ../src/main/cpp/jni/CollectionManager.cpp)

add_library(Android SHARED
        ../src/main/cpp/android/os/build/Version.cpp)

add_library(Information SHARED ../src/main/cpp/Information.cpp)

add_library(Sensor SHARED
        ../src/main/cpp/SensorEvent.cpp
        ../src/main/cpp/Sensor.cpp
        ../src/main/cpp/SensorManager.cpp
        ../src/main/cpp/sensor_event/Default.cpp
        ../src/main/cpp/sensor_event/Accelerometer.cpp
        ../src/main/cpp/sensor_event/MagneticField.cpp
        ../src/main/cpp/sensor_event/Gyroscope.cpp
        ../src/main/cpp/sensor/Default.cpp
        ../src/main/cpp/sensor/Accelerometer.cpp
        ../src/main/cpp/sensor/MagneticField.cpp
        ../src/main/cpp/sensor/Gyroscope.cpp
        ../src/main/cpp/CollectionManager.cpp)

find_library(Loglib log)

find_library(Androidlib android)

target_link_libraries(Information ${Loglib})

target_link_libraries(Android ${Loglib})

target_link_libraries(Sensor ${Loglib} ${Androidlib} Android)

target_link_libraries(Bridge ${Loglib} Information Sensor)
