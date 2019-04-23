#!/bin/bash

# Sometimes, Android Studio can't work normally for variety of reasons,
# use this script to clean project.

set -e -u

cd `dirname $0`
cd ..

rm -rf app_android/.gradle
rm -rf app_android/.idea
rm -rf app_android/*.iml
rm -rf app_android/local.properties

rm -rf app_android/app/.externalNativeBuild
rm -rf app_android/app/build
rm -rf app_android/app/*.iml

rm -rf library_android/.externalNativeBuild
rm -rf library_android/build
rm -rf library_android/*.iml
