#!/bin/bash

cd `dirname $0`

g_project_dir="app_android"
g_module_name="library"

g_src="library_android/build/outputs/aar/library-release.aar"
g_dst="app_unity/Plugins/Android/library.aar"

#1 build library
pushd $g_project_dir
./gradlew :$g_module_name:clean
./gradlew :$g_module_name:assembleRelease
popd

#2 copy the file to destination
rm -f $g_dst
mkdir -p  `dirname $g_dst`
mv $g_src $g_dst
