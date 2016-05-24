set (sources main.cpp simple_class.cpp simple_map.cpp)
set (CMAKE_BINARY_DIR bin)
add_library(objs OBJECT ${sources})
add_executable(a.out $<TARGET_OBJECTS:objs>)
