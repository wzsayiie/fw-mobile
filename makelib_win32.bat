@echo off

cd /d %~dp0

::1 generate headers
call generate_headers.bat

::2 tmp directory
set temporary=TMP

if exist %temporary% (rmdir /q /s %temporary%)
mkdir %temporary%

::3 compile
set error=0

::make sure values of !random! are different every time.
setlocal EnableDelayedExpansion

set source="library/BASIS"
call :compile
if not %error% == 0 (goto end)

set source="library/ctool"
call :compile
if not %error% == 0 (goto end)

set source="library/foundation"
call :compile
if not %error% == 0 (goto end)

set source="library/standalone"
call :compile
if not %error% == 0 (goto end)

::4 link
set out=BUILD
set exe=windows

if not exist %out% (mkdir %out%)
if exist %out%\%exe% (del %out%\%exe%)

set cmdln=cl
set cmdln=%cmdln% /nologo
set cmdln=%cmdln% /Fe%out%\%exe%
set cmdln=%cmdln% %temporary%\*.obj
set cmdln=%cmdln% shell32.lib
set cmdln=%cmdln% shlwapi.lib
%cmdln%

rmdir /q /s %temporary%

::functions
goto end

:compile
set args=/nologo /EHsc /std:c++14 /IGENERATED_HEADERS /MD
for /r %source% %%f in (*.cpp, *.cc) do (
    cl %args% /c %%f /Fo%temporary%\%%~nf.!random!.obj
)
goto end

:end
