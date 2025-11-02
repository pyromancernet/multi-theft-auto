@echo off

rem Change to repository root directory
cd /d "%~dp0\.."

rem Update CEF eventually
Utils\premake5.exe install_cef

rem Update Unifont
Utils\premake5.exe install_unifont

rem Update discord-rpc
Utils\premake5.exe install_discord

rem Generate solutions
Utils\premake5.exe vs2022

if %0 == "%~0" pause