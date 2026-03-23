@echo off
setlocal enabledelayedexpansion

echo [*] Hunting for vcpkg...

set "VCPKG_ROOT_PATH="
set "IS_TEMP=0"

for /f "tokens=*" %%i in ('where vcpkg 2^>nul') do (
    set "VCPKG_EXE_PATH=%%i"
    for %%A in ("!VCPKG_EXE_PATH!") do set "VCPKG_ROOT_PATH=%%~dpA"
    set "VCPKG_ROOT_PATH=!VCPKG_ROOT_PATH:~0,-1!"
    goto :FOUND
)

set "CANDIDATES=%VCPKG_ROOT% D:\vcpkg C:\vcpkg %USERPROFILE%\vcpkg %USERPROFILE%\Desktop\vcpkg"
for %%P in (%CANDIDATES%) do (
    if exist "%%~P\vcpkg.exe" (
        set "VCPKG_ROOT_PATH=%%~P"
        goto :FOUND
    )
)

for %%D in (C D E F G) do (
    if exist "%%D:\" (
        if exist "%%D:\vcpkg\vcpkg.exe" (set "VCPKG_ROOT_PATH=%%D:\vcpkg" & goto :FOUND)
        for /d %%G in ("%%D:\*") do (
            if exist "%%G\vcpkg\vcpkg.exe" (set "VCPKG_ROOT_PATH=%%G\vcpkg" & goto :FOUND)
            if exist "%%G\vcpkg.exe" (set "VCPKG_ROOT_PATH=%%G" & goto :FOUND)
        )
    )
)

echo [!] vcpkg not found. Installing temporary instance...
set "VCPKG_ROOT_PATH=%CD%\vcpkg_temp"
set "IS_TEMP=1"

if not exist "!VCPKG_ROOT_PATH!" (
    git clone --depth 1 https://github.com/microsoft/vcpkg.git "!VCPKG_ROOT_PATH!"
    if !errorlevel! neq 0 (echo [!] Git clone failed. & pause & exit /b 1)
)

if not exist "!VCPKG_ROOT_PATH!\vcpkg.exe" (
    pushd "!VCPKG_ROOT_PATH!"
    call .\bootstrap-vcpkg.bat
    popd
)

:FOUND
set "VCPKG_TOOLCHAIN=!VCPKG_ROOT_PATH!\scripts\buildsystems\vcpkg.cmake"
echo [+] vcpkg verified: !VCPKG_ROOT_PATH!

set "BUILD_DIR=build"
set "CONFIG=Release"

if exist %BUILD_DIR% rd /s /q %BUILD_DIR%

cmake -B %BUILD_DIR% -S . ^
    -DCMAKE_TOOLCHAIN_FILE="!VCPKG_TOOLCHAIN!" ^
    -DCMAKE_BUILD_TYPE=%CONFIG%

if %errorlevel% neq 0 (echo [!] Config failed. & pause & exit /b %errorlevel%)

cmake --build %BUILD_DIR% --config %CONFIG%

if %errorlevel% neq 0 (echo [!] Build failed. & pause & exit /b %errorlevel%)

echo.
echo [+] Build Successful!
if "!IS_TEMP!"=="1" (
    echo [*] Cleaning up temporary vcpkg installation...
    timeout /t 2 /nobreak >nul
    rd /s /q "!VCPKG_ROOT_PATH!"
    echo [+] vcpkg_temp removed.
)

echo [+] DLL: %BUILD_DIR%\%CONFIG%\Cheat.dll
pause