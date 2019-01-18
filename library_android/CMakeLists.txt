cmake_minimum_required(VERSION 3.4.1)

### configuration begin
set(LIB_NAME native)
set(INC_PATH ../library/GENERATED_HEADERS)

set(SRC_AIMS ${SRC_AIMS} ../library/bridge/jni_cpp/*.cpp)
set(SRC_AIMS ${SRC_AIMS} ../library/foundation/*.cpp)
set(SRC_AIMS ${SRC_AIMS} ../library/structure/*.cpp)
### configutation end

file(GLOB_RECURSE SRC_FILES ${SRC_AIMS})
include_directories(${INC_PATH})

add_library(${LIB_NAME} SHARED ${SRC_FILES})
target_link_libraries(${LIB_NAME} log)
