#!/bin/bash

set -e -u

cd `dirname $0`

echo "NOTE: to configurate and remove 'exit 1' on next line!"
exit 1

## configrutaion begin
##
team_uid="" # team id
bundl_id="" # bundle id

priv_key="" # "security find-identity" to list private keys stored by Keychain Access
prov_fil="" # xx.mobileprovision
prov_nam="" # name of mobileprovision

ex_methd="" # "ad-hoc", "app-store", "development" or "enterprise"

proj_dir="app_ios"
proj_fil="App.xcodeproj"
schm_nam="App"
archs_li="-arch armv7s -arch arm64 -arch arm64e"
outs_dir="BUILD"
outs_fil="app"

sh generate_headers.sh
sh cusapp_lua/generate_lua.sh
##
## configrution end

function clean_cache() {
    rm -rf $proj_dir/build
}

function build_archive() {
    local cmd_line="xcodebuild"
    cmd_line="$cmd_line -project $proj_dir/$proj_fil"
    cmd_line="$cmd_line -scheme $schm_nam"
    cmd_line="$cmd_line $archs_li"
    cmd_line="$cmd_line -configuration Release"
    cmd_line="$cmd_line BITCODE_GENERATION_MODE=bitcode"
    cmd_line="$cmd_line archive -archivePath $proj_dir/build/$schm_nam.xcarchive"
    $cmd_line
}

function resign_archive() {
    local appli_dir="$proj_dir/build/$schm_nam.xcarchive/Products/Applications/App.app"
    local sign_hash="$proj_dir/build/$schm_nam.xcarchive/Products/Applications/App.app/_CodeSignature"
    local embed_cfg="$proj_dir/build/$schm_nam.xcarchive/Products/Applications/App.app/embedded.mobileprovision"
    local embed_pli="$proj_dir/build/embedded_mobileprovision.plist"
    local entit_pli="$proj_dir/build/entitlements.plist"

    rm -rf sign_hash
    rm -rf embed_cfg
    rm -rf embed_pli
    rm -rf entit_pli

    plutil -replace CFBundleIdentifier -string "$bundl_id" $appli_dir/Info.plist
    cp $prov_fil $appli_dir

    security cms -D -i                $prov_fil  >  $embed_pli
    plutil -extract Entitlements xml1 $embed_pli -o $entit_pli

    codesign -f -s "$priv_key" --entitlements $entit_pli $appli_dir
}

function export_ipa() {
    local options_fil="$proj_dir/build/export_options.plist"

    echo "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"               > $options_fil
    echo "<!DOCTYPE plist PUBLIC"                                  >> $options_fil
    echo "    \"-//Apple//DTD PLIST 1.0//EN\""                     >> $options_fil
    echo "    \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">" >> $options_fil
    echo "<plist version="1.0">"                                   >> $options_fil
    echo "<dict>"                                                  >> $options_fil
    echo "    <key>method</key> <string>$ex_methd</string>"        >> $options_fil
    echo "    <key>teamID</key> <string>$team_uid</string>"        >> $options_fil
    echo "    <key>compileBitcode</key> <true/>"                   >> $options_fil
    echo "    <key>uploadSymbols</key> <true/>"                    >> $options_fil
    echo "    <key>provisioningProfiles</key>"                     >> $options_fil
    echo "    <dict>"                                              >> $options_fil
    echo "        <key>$bundl_id</key> <string>$prov_nam</string>" >> $options_fil
    echo "    </dict>"                                             >> $options_fil
    echo "</dict>"                                                 >> $options_fil
    echo "</plist>"                                                >> $options_fil

    local cmd_line="xcodebuild"
    cmd_line="$cmd_line -exportArchive"
    cmd_line="$cmd_line -archivePath $proj_dir/build/$schm_nam.xcarchive"
    cmd_line="$cmd_line -exportOptionsPlist $options_fil"
    cmd_line="$cmd_line -exportPath $proj_dir/build"
    $cmd_line
}

function copy_outputs() {
    mkdir -p $outs_dir
    rm -rf   $outs_dir/$outs_fil.ipa
    rm -rf   $outs_dir/$outs_fil.dSym

    mv $proj_dir/build/$schm_nam.ipa                                $outs_dir/$outs_fil.ipa
    mv $proj_dir/build/$schm_nam.xcarchive/dSYMs/$schm_nam.app.dSYM $outs_dir/$outs_fil.dSym
}

clean_cache
build_archive
resign_archive
export_ipa
copy_outputs
