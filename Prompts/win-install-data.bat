@echo off

rem Change to repository root directory
cd /d "%~dp0\.."

rem Install data files
Utils\premake5 install_data

if %0 == "%~0" pause