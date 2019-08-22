@echo off

pushd %~dp0

set cmd_line=
set cmd_line=%cmd_line% Unity
set cmd_line=%cmd_line% -quit
set cmd_line=%cmd_line% -batchmode
set cmd_line=%cmd_line% -buildTarget Android
set cmd_line=%cmd_line% -projectPath %cd%\app_unity
set cmd_line=%cmd_line% -executeMethod AndroidBuilder.Build
set cmd_line=%cmd_line% -logFile

%cmd_line%

popd
