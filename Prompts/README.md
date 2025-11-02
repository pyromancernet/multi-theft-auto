# Build Scripts

This directory contains build and installation scripts for Multi Theft Auto.

## Windows Scripts

- **win-create-projects.bat** - Generates Visual Studio solution files
- **win-build.bat** - Builds the project (usage: `win-build.bat [Debug|Release] [Win32|x64|ARM|ARM64]`)
- **win-install-data.bat** - Installs data files and optionally resources

## Linux/macOS Scripts

- **linux-build.sh** - Builds the project on Linux/macOS (usage: `./linux-build.sh [--arch=x86|x64|arm|arm64] [--config=debug|release] [--cores=<n>]`)
- **linux-install-data.sh** - Installs data files and optionally resources on Linux/macOS

## Wine Scripts

- **wine-build.sh** - Builds the Windows version using Wine and MSVC (usage: `./wine-build.sh [Debug|Release] [Win32|x64|ARM|ARM64]`)

## Usage

All scripts should be run from the repository root or can be executed directly from this directory (they automatically change to the root).

### Examples

```bash
# Windows
Prompts\win-create-projects.bat
Prompts\win-build.bat Release x64
Prompts\win-install-data.bat

# Linux/macOS
./Prompts/linux-build.sh --arch=x64 --config=release
./Prompts/linux-install-data.sh
```
