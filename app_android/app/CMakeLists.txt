cmake_minimum_required(VERSION 3.4.1)

file(GLOB_RECURSE SOURCES src/main/cpp/*.cpp)

add_library(native SHARED ${SOURCES})
target_link_libraries(native log)
