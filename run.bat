@echo off

:: Build first
call build.bat
if errorlevel 1 (
    echo Build failed!
    exit /b 1
)

:: Run the executable
echo Running beluga.exe...
".\build\beluga.exe" 