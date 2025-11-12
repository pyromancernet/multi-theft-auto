@echo off
setlocal enabledelayedexpansion

echo.
echo ============================================================
echo Multi Theft Auto - Retry Downloads
echo ============================================================
echo.

set "attempts=0"
set "max_attempts=3"

:retry_downloads
set /a attempts=!attempts! + 1
echo [ATTEMPT %attempts%/%max_attempts%] Retrying downloads...
echo.

echo Downloading CEF...
..\utils\premake5.exe --file=..\premake5.lua install_cef
set cef_result=%errorlevel%

echo Downloading Unifont...
..\utils\premake5.exe --file=..\premake5.lua install_unifont
set unifont_result=%errorlevel%

echo Downloading Discord-RPC...
..\utils\premake5.exe --file=..\premake5.lua install_discord
set discord_result=%errorlevel%

if %cef_result% equ 0 if %unifont_result% equ 0 if %discord_result% equ 0 (
    echo.
    echo [SUCCESS] All downloads completed successfully!
    echo.
    goto success
)

if %attempts% lss %max_attempts% (
    echo.
    echo [RETRY] Some downloads failed. Waiting 10 seconds before retry...
    timeout /t 10 /nobreak
    echo.
    goto retry_downloads
)

echo.
echo [WARNING] Downloads still failing after %max_attempts% attempts.
echo Possible causes:
echo  - Network connectivity issues
echo  - Download servers temporarily unavailable
echo  - Firewall/proxy blocking downloads
echo.
echo You can:
echo  1. Check your internet connection
echo  2. Try again later
echo  3. Download files manually from GitHub releases
echo.
goto end

:success
echo.
echo ============================================================
echo All dependencies downloaded successfully!
echo You can now run win-create-projects.bat
echo ============================================================
echo.

:end
if %0 == "%~0" pause
endlocal
