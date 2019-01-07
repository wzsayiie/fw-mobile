cmake_minimum_required(VERSION 3.4.1)

file(GLOB_RECURSE SOURCES ../library/cpp/library/*.cpp)

include_directories(
        ../library/cpp/library/bridge_core
        ../library/cpp/library/bridge
        ../library/cpp/library/foundation)

add_library(library SHARED ${SOURCES})
target_link_libraries(library log)
