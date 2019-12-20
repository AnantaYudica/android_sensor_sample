cmake_minimum_required(VERSION 3.4.1)

add_compile_options(-std=c++11)

add_library(Bridge SHARED ../src/main/cpp/Bridge.cpp)

find_library(Loglib log)

target_link_libraries(Bridge ${Loglib})