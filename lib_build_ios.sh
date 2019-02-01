#!/bin/bash

set -e -u

cd `dirname $0`

### configuration begin
projct_dir="library_ios"
projct_fil="Library.xcodeproj"
target_nam="Library"
archs_list="x86_64 arm64 arm64e"
ultima_dir="app_unity/Plugins/iOS"
ultima_fil="libLibrary.a"
### configutation end

# build library
function clean_cache() {
    rm -rf $projct_dir/build
}

function build_archive() {
    local arch_item=$1
    if [ "$arch_item" = "i386" -o "$arch_item" = "x86_64" ]; then
        local sdk_type="iphonesimulator"
    else
        local sdk_type="iphoneos"
    fi

    local cmd_line="xcodebuild"
    cmd_line="$cmd_line -project $projct_dir/$projct_fil"
    cmd_line="$cmd_line -target $target_nam"
    cmd_line="$cmd_line -arch $arch_item"
    cmd_line="$cmd_line -sdk $sdk_type"
    cmd_line="$cmd_line -configuration Release"
    cmd_line="$cmd_line CONFIGURATION_BUILD_DIR=build/outputs"
    $cmd_line

    local old_name=$projct_dir/build/outputs/lib$target_nam.a
    local new_name=$projct_dir/build/outputs/lib$target_nam.$arch_item.a
    mv $old_name $new_name
}

function merge_archives() {
    local thin_archs="$projct_dir/build/outputs/lib$target_nam.*.a"
    local merged_lib="$projct_dir/build/outputs/$ultima_fil"
    lipo -create $thin_archs -output $merged_lib
}

sh GENERATE_HEADERS.sh

clean_cache
for arch_item in $archs_list; do
    build_archive $arch_item
done
merge_archives

# copy the library
mkdir -p                                 $ultima_dir
mv $projct_dir/build/outputs/$ultima_fil $ultima_dir
