add_library(objs OBJECT main.cpp simple_class.cpp simple_map.cpp)
add_executable(a.out $<TARGET_OBJECTS:objs>)
