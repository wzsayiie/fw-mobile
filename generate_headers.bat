@echo off

pushd %~dp0

::This batch will traverse headers and create new homonymic headers reference former.
::It will avoid developer adding vast header search paths tediously.

set destination=GENERATED_HEADERS

if exist %destination% (rmdir /q /s %destination%)
mkdir %destination%

set error=0

set source="library0"
call :generate
if not %error% == 0 (goto end)

set source="program_app"
call :generate
if not %error% == 0 (goto end)

set source="program_game"
call :generate
if not %error% == 0 (goto end)

set source="program_gl"
call :generate
if not %error% == 0 (goto end)

goto end

:generate
for /r %source% %%f in (*.h*) do (
    if exist %~dp0\%destination%\%%~nxf (
        echo error: homonymic header '%%~nxf'
        rmdir /q /s %destination%
        set error=1
        goto end
    ) else (
        echo #include "%%f" >> %~dp0\%destination%\%%~nxf
    )
)

:end

popd
