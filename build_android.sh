#!/bin/bash

cd `dirname $0`

project_dir="app_android"
flavor_name="master"
ultima_path="build"
ultima_file="app-master.apk"

origin_path="$project_dir/app/build/outputs/apk/$flavor_name/release"
origin_file="app-$flavor_name-release.apk"

# build library
pushd $project_dir
./gradlew clean
./gradlew assembleRelease
popd

# copy apk
mkdir -p                     $ultima_path
rm -f                        $ultima_path/$ultima_file
mv $origin_path/$origin_file $ultima_path
mv $ultima_path/$origin_file $ultima_path/$ultima_file
