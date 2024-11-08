@echo off
setlocal enabledelayedexpansion

:: Ensure build directory exists
if not exist ".\build" mkdir ".\build"

:: Create a sorted list of all files and hash them
set "fileList="
for /f "delims=" %%F in ('dir /b /s /a-d "src\*" ^| sort') do (
    set "fileList=!fileList!%%~nxF;"
)

:: Create a temporary file for the file list
echo !fileList! > ".\build\temp_files.txt"

:: Generate hash of the file list
set "currentHash="
for /f "delims=" %%H in ('certutil -hashfile ".\build\temp_files.txt" MD5 ^| findstr /v "hash CertUtil"') do (
    set "currentHash=%%H"
)
del ".\build\temp_files.txt"

:: Read the previous hash from a temp file
set "prevHash="
if exist ".\build/src_files_hash.txt" (
    set /p prevHash=<".\build/src_files_hash.txt"
) else (
    echo No previous hash found. Generating build files...
    call gen.bat
)

set "currentHash=%currentHash: =%"
set "prevHash=%prevHash: =%"

:: If hash changed, regenerate build files
if not "%currentHash%"=="%prevHash%" (
    echo Source files changed. Regenerating build files...
    call gen.bat
    echo Writing new hash to build/src_files_hash.txt
    echo !currentHash! > ".\build/src_files_hash.txt"
    if errorlevel 1 (
        echo Error: Could not write to hash file
        exit /b 1
    )
)

:: Build the project
ninja -C build