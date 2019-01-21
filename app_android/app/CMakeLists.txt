cmake_minimum_required(VERSION 3.4.1)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(built_jni_subpath build/intermediates/library_and_local_jars_jni/release/${ANDROID_ABI})
else()
    set(built_jni_subpath build/intermediates/library_and_local_jars_jni/debug/${ANDROID_ABI})
endif()

function(get_absolute_paths paths)
    foreach(it ${${paths}})
        list(APPEND abs_paths ${CMAKE_CURRENT_SOURCE_DIR}/${it})
    endforeach()
    set(${paths} ${abs_paths} PARENT_SCOPE)
endfunction()

### configuration begin
set(lib_name native)

list(APPEND inc_path ../../library/GENERATED_HEADERS)
list(APPEND src_aims src/main/cpp/*.cpp)
list(APPEND usr_libs ../../library_android/${built_jni_subpath}/liblibrary.so)
### configutation end

include_directories(${inc_path})

file(GLOB_RECURSE src_files ${src_aims})
add_library(${lib_name} SHARED ${src_files})

get_absolute_paths(usr_libs)
target_link_libraries(${lib_name} ${usr_libs})
