@echo off
setlocal
set "MODITE_BUILD=%~dp0..\build\web"
set "MODITE_CMAKE="

if exist "%MODITE_BUILD%\CMakeCache.txt" (
    for /f "usebackq tokens=1,* delims==" %%A in ("%MODITE_BUILD%\CMakeCache.txt") do (
        if "%%A"=="CMAKE_COMMAND:INTERNAL" set "MODITE_CMAKE=%%B"
    )
)

if not defined MODITE_CMAKE (
    echo Configure build/web with Emscripten in Rider first. 1>&2
    exit /b 1
)

"%MODITE_CMAKE%" --build "%MODITE_BUILD%" --target run-web
exit /b %ERRORLEVEL%
