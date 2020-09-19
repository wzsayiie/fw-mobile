cmake_minimum_required(VERSION 3.4.1)

### configuration begin
set(lib_name library)

list(APPEND inc_path ../GENERATED_HEADERS)

list(APPEND src_aims ../library0/BASIS/*.c[xp][xp])
list(APPEND src_aims ../library0/ctool/*.c[xp][xp])
list(APPEND src_aims ../library0/foundation/*.c[xp][xp])
list(APPEND src_aims ../library0/subsystem/*.c[xp][xp])
### configutation end

file(GLOB_RECURSE src_files ${src_aims})

add_compile_options  (-Wno-nonportable-include-path) #ignore when header path contains "\".
add_compile_options  (-std=c++14)
include_directories  (${inc_path})
add_library          (${lib_name} SHARED ${src_files})
target_link_libraries(${lib_name})
