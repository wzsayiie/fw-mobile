cmake_minimum_required(VERSION 3.4.1)

## NOTE: these paths are different for different Android Studio versions. the followed starts from 3.6 .
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(built_jni_subpath build/intermediates/library_jni/release/jni/${ANDROID_ABI})
else()
    set(built_jni_subpath build/intermediates/library_jni/debug/jni/${ANDROID_ABI})
endif()

function(convert_to_absolute_paths paths)
    foreach(it ${${paths}})
        list(APPEND abs_paths ${CMAKE_CURRENT_SOURCE_DIR}/${it})
    endforeach()
    set(${paths} ${abs_paths} PARENT_SCOPE)
endfunction()

### configuration begin
set(lib_name app)

list(APPEND inc_path ../../GENERATED_HEADERS)
list(APPEND src_aims src/main/cpp/*.cxx)

list(APPEND sys_libs log)
list(APPEND usr_libs ../../library_android/${built_jni_subpath}/liblibrary.so)
### configutation end

file(GLOB_RECURSE src_files ${src_aims})
convert_to_absolute_paths(usr_libs)

add_compile_options  (-Wno-nonportable-include-path) # ignore when header path contains "\".
add_compile_options  (-std=c++14)
include_directories  (${inc_path})
add_library          (${lib_name} SHARED ${src_files})
target_link_libraries(${lib_name} ${sys_libs} ${usr_libs})
