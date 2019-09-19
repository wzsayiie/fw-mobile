@echo off

pushd %~dp0

::: configuration begin
set projct_dir="app_android"
set ultima_dir="BUILD"
set ultima_fil="as.apk"

call generate_headers.bat
call program_game\generate_lua.bat
::: configutation end

:: NOTE:
:: file 'local.properties' has a higher priority than the environment variables
set     ANDROID_HOME=%USERPROFILE%\AppData\Local\Android\Sdk
set ANDROID_NDK_HOME=%USERPROFILE%\AppData\Local\Android\Sdk\ndk-bundle

::build
pushd %projct_dir%
call gradlew.bat clean
call gradlew.bat assembleRelease
popd

::move
if not exist %ultima_dir% (
    mkdir    %ultima_dir%
)
if exist %ultima_dir%\%ultima_fil% (
    del  %ultima_dir%\%ultima_fil%
)
set apk_fm="%projct_dir%\app\build\outputs\apk\release\app-release.apk"
set apk_to="%ultima_dir%\%ultima_fil%"
move %apk_fm% %apk_to%

popd
