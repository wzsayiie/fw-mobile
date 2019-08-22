@echo off

:: Sometimes, Android Studio can't work normally for variety of reasons,
:: use this script to clean project.

pushd %~dp0\..

            set target=app_android\.gradle
call :rmp & set target=app_android\.idea
call :rmp & set target=app_android\app_android.iml
call :rmp & set target=app_android\local.properties

call :rmp & set target=app_android\app\.externalNativeBuild
call :rmp & set target=app_android\app\build
call :rmp & set target=app_android\app\app.iml

call :rmp & set target=library_android\.externalNativeBuild
call :rmp & set target=library_android\build
call :rmp & set target=library_android\library.iml
call :rmp

goto end

:rmp
if exist %target%\nul (
    ::is a directory
    rmdir /q /s %target%
) else (
    if exist %target% (
        del %target%
    )
)
goto end

:end

popd
