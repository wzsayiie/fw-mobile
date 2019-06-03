cmake_minimum_required(VERSION 3.4.1)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(built_jni_subpath build/intermediates/intermediate-jars/release/jni/${ANDROID_ABI})
else()
    set(built_jni_subpath build/intermediates/intermediate-jars/debug/jni/${ANDROID_ABI})
endif()

function(get_absolute_paths paths)
    foreach(it ${${paths}})
        list(APPEND abs_paths ${CMAKE_CURRENT_SOURCE_DIR}/${it})
    endforeach()
    set(${paths} ${abs_paths} PARENT_SCOPE)
endfunction()

### configuration begin
set(lib_name cargo)

list(APPEND inc_path ../../GENERATED_HEADERS)
list(APPEND inc_path ../../thirds_android/includes)

list(APPEND src_aims ../../program_basis/*.cpp)
list(APPEND src_aims ../../program_cpp/*.cpp)
list(APPEND src_aims ../../program_lua/*.cpp)

list(APPEND sys_libs log)
list(APPEND sys_libs GLESv2)
list(APPEND usr_libs ../../thirds_android/jniLibs/${ANDROID_ABI}/liblua.so)
list(APPEND usr_libs ../../library_android/${built_jni_subpath}/liblibrary.so)
### configutation end

include_directories(${inc_path})

file(GLOB_RECURSE src_files ${src_aims})
add_library(${lib_name} SHARED ${src_files})

get_absolute_paths(usr_libs)
target_link_libraries(${lib_name} ${sys_libs} ${usr_libs})
