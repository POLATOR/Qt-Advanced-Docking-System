@echo off
setlocal EnableDelayedExpansion
set EXTERNAL_LIBS=%~1
set CMAKE_EXE=%~2
if "%EXTERNAL_LIBS%"=="" goto usage
if "!CMAKE_EXE!"=="" (
    set CMAKE_EXE="%ProgramFiles(x86)%\CMake\bin\cmake.exe"
    if not exist !CMAKE_EXE! set CMAKE_EXE="%ProgramW6432%\CMake\bin\cmake.exe"
    if not exist !CMAKE_EXE! (
        echo CMake not installed in default location
        exit /B 1
    )
) else (
    if not exist !CMAKE_EXE! (
        echo CMake [!CMAKE_EXE!] not found
        exit /B 1
    )
)
if exist .build (
    echo Removing build dir...
    rd /q /s .build
)
mkdir .build
pushd .build
!CMAKE_EXE! .. -G "Visual Studio 16 2019" -A x64 "-DCMAKE_PREFIX_PATH=%EXTERNAL_LIBS%"
if errorlevel 1 (
    pause
    popd
    exit /B 1
)
popd
exit /B 0

:usage
echo Usage: %0 qt_dir [cmake_exe]
echo where:
echo     qt_dir - the directory where the Qt libraries were installed
echo     cmake_exe - full path to cmake.exe. If no parameter is specified, the default CMake installation will be used.
exit /B 1
