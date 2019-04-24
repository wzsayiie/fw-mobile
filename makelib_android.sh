#!/bin/bash

set -e -u

cd `dirname $0`

### configuration begin
projct_dir="app_android"
module_dir="library_android"
module_nam="library"
ultima_dir="app_unity/Assets/Plugins/Android"
ultima_fil="library.aar"

sh generate_headers.sh
### configutation end

origin_dir="$module_dir/build/outputs/aar"
origin_fil="$module_nam-release.aar"

# clean
rm -rf $ultima_dir/$ultima_fil

# build library
pushd $projct_dir
./gradlew :$module_nam:clean
./gradlew :$module_nam:assembleRelease
popd

# copy file
mkdir -p                   $ultima_dir
cp $origin_dir/$origin_fil $ultima_dir
mv $ultima_dir/$origin_fil $ultima_dir/$ultima_fil
