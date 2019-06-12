cmake_minimum_required(VERSION 3.4.1)

function(get_absolute_paths paths)
    foreach(it ${${paths}})
        list(APPEND abs_paths ${CMAKE_CURRENT_SOURCE_DIR}/${it})
    endforeach()
    set(${paths} ${abs_paths} PARENT_SCOPE)
endfunction()

### configuration begin
set(lib_name library)

list(APPEND inc_path ../GENERATED_HEADERS)

list(APPEND src_aims ../library/BASIS/*.cpp)
list(APPEND src_aims ../library/foundation/*.cpp)
list(APPEND src_aims ../library/subsystem/*.cpp)

#list(APPEND sys_libs xx)
#list(APPEND usr_libs ../xx/xx.so)

### configutation end

include_directories(${inc_path})

file(GLOB_RECURSE src_files ${src_aims})
add_library(${lib_name} SHARED ${src_files})

get_absolute_paths(usr_libs)
target_link_libraries(${lib_name} ${sys_libs} ${usr_libs})
