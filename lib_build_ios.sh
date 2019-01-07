#!/bin/bash

cd `dirname $0`

g_proj_root="library_ios"
g_proj_file="Library.xcodeproj"
g_trgt_name="Library"

g_dst="app_unity/Plugins/iOS"

#1 build library
function build_library() {
    local arch_name=$1
    local sdk_type=$2

    local cmd_line="xcodebuild"
    cmd_line="$cmd_line -project $g_proj_root/$g_proj_file"
    cmd_line="$cmd_line -target $g_trgt_name"
    cmd_line="$cmd_line -arch $arch_name"
    cmd_line="$cmd_line -sdk $sdk_type"
    cmd_line="$cmd_line -configuration Release"
    cmd_line="$cmd_line CONFIGURATION_BUILD_DIR=build/output"
    $cmd_line

    local old_name=$g_proj_root/build/output/lib$g_trgt_name.a
    local new_name=$g_proj_root/build/output/lib$g_trgt_name.$arch_name.a
    mv $old_name $new_name
}

function merge_libraries() {
    local thin_libs="$g_proj_root/build/output/lib$g_trgt_name.*.a"
    local merge_one="$g_proj_root/build/output/lib$g_trgt_name.a"
    lipo -create $thin_libs -output $merge_one
}

build_library x86_64 iphonesimulator
build_library arm64  iphoneos
build_library arm64e iphoneos

merge_libraries

#2 copy the library to destination
mkdir -p $g_dst
cp $g_proj_root/build/output/lib$g_trgt_name.a $g_dst

#3 remove temporary file
rm -rf $g_proj_root/build
