cmake_minimum_required(VERSION 3.4.1)

file(GLOB_RECURSE SOURCES
        ../library/bridge/jni_cpp/*.cpp
        ../library/foundation/*.cpp
        ../library/structure/*.cpp)

include_directories(../library/GENERATED_HEADERS)

add_library(library SHARED ${SOURCES})
target_link_libraries(library log)
