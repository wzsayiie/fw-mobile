#!/bin/bash

set -e -u

cd `dirname $0`

### configuration begin
projct_dir="app_android"
module_dir="library_android"
module_nam="library"
ultima_dir="app_unity/Plugins/Android"
ultima_fil="library.aar"
### configutation end

origin_dir="$module_dir/build/outputs/aar"
origin_fil="$module_nam-release.aar"

# build library
sh generate_headers.sh

pushd $projct_dir
./gradlew :$module_nam:clean
./gradlew :$module_nam:assembleRelease
popd

# copy file
mv $origin_dir/$origin_fil $origin_dir/$ultima_fil
mkdir -p                   $ultima_dir
mv $origin_dir/$ultima_fil $ultima_dir
