@echo off

pushd %~dp0

::: configuration begin
set projct_dir="app_android"
set module_dir="library_android"
set module_nam="library"
set ultima_dir="BUILD"
set ultima_fil="android.aar"

call generate_headers.bat
::: configutation end

:: NOTE:
:: file 'local.properties' has a higher priority than the environment variables
set     ANDROID_HOME=%USERPROFILE%\AppData\Local\Android\Sdk
set ANDROID_NDK_HOME=%USERPROFILE%\AppData\Local\Android\Sdk\ndk-bundle

::build
pushd %projct_dir%
call gradlew.bat :%module_nam%:clean
call gradlew.bat :%module_nam%:assembleRelease
popd

::move
if not exist %ultima_dir% (
    mkdir    %ultima_dir%
)
if exist %ultima_dir%\%ultima_fil% (
    del  %ultima_dir%\%ultima_fil%
)
set aar_fm="%module_dir%\build\outputs\aar\%module_nam%-release.aar"
set aar_to="%ultima_dir%\%ultima_fil%"
move %aar_fm% %aar_to%

popd
