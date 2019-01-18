#!/bin/bash

# This script will traverse all headers in current diretory,
# and create new homonymic headers reference former.
# It will avoid developer adding vast header search paths tediously.

set -e -u

cd `dirname $0`

libra_path=`pwd`
output_dir="GENERATED_HEADERS"
find_trget="*.h"

# remove current files
rm -rf $output_dir

# new files
mkdir -p $output_dir
pushd    $output_dir

for header_item in `find $libra_path -name "$find_trget"`; do
    echo "#include \"$header_item\"" > `basename $header_item`
done

popd
