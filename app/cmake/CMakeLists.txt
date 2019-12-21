cmake_minimum_required(VERSION 3.4.1)

add_compile_options(-std=c++11)

add_library(Bridge SHARED ../src/main/cpp/Bridge.cpp)

add_library(Information SHARED ../src/main/cpp/Information.cpp)

find_library(Loglib log)

target_link_libraries(Information ${Loglib})

target_link_libraries(Bridge ${Loglib} Information)
