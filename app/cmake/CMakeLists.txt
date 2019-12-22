cmake_minimum_required(VERSION 3.4.1)

add_compile_options(-std=c++11)

add_library(Bridge SHARED ../src/main/cpp/Bridge.cpp)

add_library(Information SHARED ../src/main/cpp/Information.cpp)

add_library(Sensor SHARED ../src/main/cpp/Sensor.cpp)

find_library(Loglib log)

find_library(Androidlib android)

target_link_libraries(Information ${Loglib})

target_link_libraries(Sensor ${Loglib} ${Androidlib})

target_link_libraries(Bridge ${Loglib} Information Sensor)
