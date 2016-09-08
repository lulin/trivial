cmake_minimum_required(VERSION 2.8)
set (sources main.cpp simple_class.cpp simple_map.cpp person.cpp)
add_library(objs OBJECT ${sources})
add_executable(a.out $<TARGET_OBJECTS:objs>)

include_directories(../include)
