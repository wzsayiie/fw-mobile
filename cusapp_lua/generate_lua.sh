#!/bin/bash

set -e -u

cd `dirname $0`

search_path="libluacusappscript"
output_file="../GENERATED_LUA/GENERATED_LUA"

rm -rf $output_file
mkdir -p `dirname $output_file`

for lua_file in `find $search_path -name "*.lua"`; do
    echo "\"`basename $lua_file`\"," >> $output_file
    echo "R\"===(`cat $lua_file`\n)===\"," >> $output_file
done
