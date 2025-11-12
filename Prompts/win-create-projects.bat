@echo off
setlocal enabledelayedexpansion

echo.
echo ============================================================
echo Multi Theft Auto - Project Setup Script
echo ============================================================
echo.

rem Define colors for output
set "success=[OK]"
set "error=[ERROR]"
set "info=[INFO]"

echo !info! Starting project setup...
echo.

rem Update CEF eventually
echo !info! Downloading CEF (this may take a few minutes)...
..\utils\premake5.exe --file=..\premake5.lua install_cef
if errorlevel 1 (
    echo !error! CEF download failed. You can try again later or download manually.
    echo.
) else (
    echo !success! CEF installed successfully.
)

rem Update Unifont
echo !info! Downloading Unifont...
..\utils\premake5.exe --file=..\premake5.lua install_unifont
if errorlevel 1 (
    echo !error! Unifont download failed. You can try again later or download manually.
    echo.
) else (
    echo !success! Unifont installed successfully.
)

rem Update discord-rpc
echo !info! Downloading Discord-RPC...
..\utils\premake5.exe --file=..\premake5.lua install_discord
if errorlevel 1 (
    echo !error! Discord-RPC download failed. You can try again later or download manually.
    echo.
) else (
    echo !success! Discord-RPC installed successfully.
)

rem Generate solutions
echo.
echo !info! Generating Visual Studio 2022 project files...
..\utils\premake5.exe --file=..\premake5.lua vs2022
if errorlevel 1 (
    echo !error! Project generation failed!
    echo Please check the error messages above.
    if %0 == "%~0" pause
    exit /b 1
) else (
    echo !success! Visual Studio project files generated successfully.
    echo.
    echo ============================================================
    echo Setup complete! Open MTASA.sln in the Build folder to start.
    echo ============================================================
    echo.
)

if %0 == "%~0" pause
endlocal