#!/bin/bash

set -e -u

cd `dirname $0`

### configuration begin
projct_dir="library_ios"
projct_fil="Resource.xcodeproj"
target_nam="Resource"
ultima_dir="app_unity/Assets/Plugins/iOS"
ultima_fil="Resource.bundle"
### configutation end

# clean
rm -rf $projct_dir/export/$ultima_fil
rm -rf $ultima_dir/$ultima_fil

# build
cmd_line="xcodebuild"
cmd_line="$cmd_line -project $projct_dir/$projct_fil"
cmd_line="$cmd_line -target $target_nam"
cmd_line="$cmd_line -configuration Release"
cmd_line="$cmd_line CONFIGURATION_BUILD_DIR=export"
$cmd_line

# copy
mkdir -p                             $ultima_dir
cp -r $projct_dir/export/$ultima_fil $ultima_dir
