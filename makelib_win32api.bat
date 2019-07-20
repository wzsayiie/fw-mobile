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

set source="library/BASIS/libbasis"
call :compile_cpp
if not %error% == 0 (goto end)

set source="library/ctool/libctool"
call :compile_cpp
if not %error% == 0 (goto end)

set source="library/foundation/libfoundation"
call :compile_cpp
if not %error% == 0 (goto end)

set source="library/foundation/win32api"
call :compile_c
if not %error% == 0 (goto end)

set source="library/standalone/libstandalone"
call :compile_cpp
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

:compile_cpp
set args=/nologo /EHsc /std:c++14 /IGENERATED_HEADERS /MD
for /r %source% %%f in (*.cpp) do (
    cl %args% /c %%f /Fo%temporary%\%%~nf.!random!.obj
)
goto end

:compile_c
set args=/nologo /IGENERATED_HEADERS /MD
for /r %source% %%f in (*.c) do (
    cl %args% /c %%f /Fo%temporary%\%%~nf.!random!.obj
)
goto end

:end