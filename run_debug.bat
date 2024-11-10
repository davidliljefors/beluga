@echo off

:: Build first
call build.bat
if errorlevel 1 (
    echo Build failed!
    exit /b 1
)

setlocal


REM Start the target executable and get its process ID
start "" "%~dp0build\beluga.exe" -waitForDebugger
set "exeName=beluga"

REM Call PowerShell to attach Visual Studio to the process
powershell -Command "& { .\\vs_attach.ps1 -ProcessName '%exeName%' }"

endlocal