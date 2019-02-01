cmake_minimum_required(VERSION 3.4.1)

### configuration begin
set(lib_name library)

list(APPEND inc_path ../library/GENERATED_HEADERS)

list(APPEND src_aims ../library/bridge/*.cpp)
list(APPEND src_aims ../library/extension/*.cpp)
list(APPEND src_aims ../library/foundation/*.cpp)

list(APPEND usr_libs log)
### configutation end

include_directories(${inc_path})

file(GLOB_RECURSE src_files ${src_aims})
add_library(${lib_name} SHARED ${src_files})

target_link_libraries(${lib_name} ${usr_libs})
