@echo off

pushd %~dp0

set cmd_line=
set cmd_line=%cmd_line% Unity.exe
set cmd_line=%cmd_line% -quit
set cmd_line=%cmd_line% -batchmode
set cmd_line=%cmd_line% -projectPath %cd%\app_unity
set cmd_line=%cmd_line% -executeMethod SDKExporter.Export
set cmd_line=%cmd_line% -logFile

%cmd_line%

popd
