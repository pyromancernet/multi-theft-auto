# Building Multi Theft Auto from Source

This document provides comprehensive instructions for building Multi Theft Auto: San Andreas from source code.

## 📋 Table of Contents

- [System Requirements](#system-requirements)
- [Windows Build Guide](#windows-build-guide)
- [Linux Build Guide](#linux-build-guide)
- [Troubleshooting](#troubleshooting)
- [Advanced Topics](#advanced-topics)

---

## System Requirements

### Windows
- **OS:** Windows 10 or Windows 11
- **Disk Space:** ~15 GB (including Visual Studio and dependencies)
- **RAM:** 8 GB minimum, 16 GB recommended
- **CPU:** Multi-core processor recommended for faster builds

### Linux
- **OS:** Any modern GNU/Linux distribution
- **Architectures:** x86, x86_64, armhf, arm64
- **Disk Space:** ~5 GB
- **RAM:** 4 GB minimum, 8 GB recommended

---

## Windows Build Guide

### Step 1: Install Prerequisites

#### 1.1 Visual Studio 2022

1. Download [Visual Studio 2022 Community Edition](https://visualstudio.microsoft.com/vs/) (free)
2. During installation, select:
   - ✅ **Workloads** → "Desktop development with C++"
   - ✅ **Individual Components** → "C++ MFC for latest v143 build tools (x86 & x64)"

**Modifying Existing Installation:**
- Open "Visual Studio Installer"
- Click "Modify" on your VS 2022 installation
- Add missing components

#### 1.2 DirectX SDK (August 2009)

> ⚠️ **Critical:** This specific version is required. Newer versions are not compatible.

1. Download DirectX SDK (August 2009):
   - [Mirror 1 (Archive.org)](https://archive.org/download/dxsdk_aug09/DXSDK_Aug09.exe)
   - [Mirror 2 (Mega.nz)](https://mega.nz/file/pQJCiAJY#jBcYT6ZP4DMBpnm12BLRto9EQ-RjjpP3BWkSPanpvLI)
   - [File hashes for verification](https://wiki.multitheftauto.com/wiki/Compiling_MTASA/DXSDK_Aug09_Hashes)

2. Run the installer
3. **Restart your computer** (required for `DXSDK_DIR` environment variable)

**S1023 Error Fix:**
If you encounter error S1023 during installation:
- Follow Microsoft's guide: [S1023 Error Fix](https://support.microsoft.com/en-us/kb/2728613)
- Usually caused by newer VC++ redistributables
- May require uninstalling newer redistributables temporarily

#### 1.3 Git (Optional but Recommended)

- [Download Git for Windows](https://git-scm.com/download/win)
- Allows easy updates and contribution workflow
- Alternative: Download source as [ZIP archive](https://github.com/multitheftauto/mtasa-blue/archive/master.zip)

### Step 2: Get Source Code

**Option A: Using Git (Recommended)**
```bash
git clone https://github.com/multitheftauto/mtasa-blue.git
cd mtasa-blue
```

**Option B: Direct Download**
- Download: [master.zip](https://github.com/multitheftauto/mtasa-blue/archive/master.zip)
- Extract to your desired location

### Step 3: Build the Project

#### Quick Build (Recommended)

```batch
# Default build (Release, Win32)
Prompts\win-build.bat

# Specific configuration examples
Prompts\win-build.bat Release x64
Prompts\win-build.bat Debug Win32
Prompts\win-build.bat Release ARM64
```

**What the script does:**
1. Downloads dependencies (CEF, Unifont, Discord RPC)
2. Generates Visual Studio solution files
3. Compiles using MSBuild
4. Outputs to `Bin/` directory

#### Manual Build (Alternative)

**Step 3.1: Generate Project Files**
```batch
Prompts\win-create-projects.bat
```

This script:
- Downloads CEF (Chromium Embedded Framework)
- Downloads Unifont
- Downloads Discord RPC library
- Generates `Build/MTASA.sln`

**Step 3.2: Open Visual Studio**
1. Open `Build/MTASA.sln`
2. Select configuration:
   - **Configuration:** `Debug` or `Release`
   - **Platform:** `Win32`, `x64`, `ARM`, or `ARM64`

**Step 3.3: Build**
- Press `F7` or select `Build > Build Solution`
- Build time: 5-20 minutes depending on hardware

**Step 3.4: Install Data Files**
```batch
Prompts\win-install-data.bat
```

This script:
- Copies essential files to `Bin/`
- Prompts to download official resources (select "y" for server)

### Step 4: Run MTA

#### Client
```batch
cd Bin
# Release build
Multi Theft Auto.exe

# Debug build (with debug symbols)
Multi Theft Auto_d.exe
```

#### Server
1. **Install Resources (First Time Only):**
   - Download [official resources](https://github.com/multitheftauto/mtasa-resources)
   - Extract to `Bin/server/mods/deathmatch/resources/`
   - Or select "y" when running `win-install-data.bat`

2. **Start Server:**
   ```batch
   cd Bin\server
   # Release build
   "MTA Server.exe"
   
   # Debug build
   "MTA Server_d.exe"
   ```

---

## Linux Build Guide

### Prerequisites

#### Install Dependencies

**Ubuntu/Debian:**
```bash
sudo apt-get update
sudo apt-get install -y \
    build-essential \
    make \
    gcc-10 g++-10 \
    libncurses-dev \
    libmysqlclient-dev \
    git
```

**Fedora/RHEL:**
```bash
sudo dnf install -y \
    make \
    gcc gcc-c++ \
    ncurses-devel \
    mysql-devel \
    git
```

**Arch Linux:**
```bash
sudo pacman -S base-devel ncurses mysql git
```

> 💡 **Tip:** Check `Utils/docker/Dockerfile` for most up-to-date dependency list

### Build Methods

#### Method 1: Automated Script (Recommended)

```bash
# Clone repository
git clone https://github.com/multitheftauto/mtasa-blue.git
cd mtasa-blue

# Build (x64, release)
./Prompts/linux-build.sh

# Build with options
./Prompts/linux-build.sh --arch=x64 --config=release --cores=8
./Prompts/linux-build.sh --arch=x86 --config=debug --cores=4

# Install data files
./Prompts/linux-install-data.sh
```

**Script Options:**
- `--arch` → `x86`, `x64`, `arm`, `arm64` (default: `x64`)
- `--config` → `debug`, `release` (default: `release`)
- `--cores` → Number of parallel jobs (default: CPU cores)

> ⚠️ **Warning:** Script deletes `Build/` and `Bin/` for clean builds

#### Method 2: Manual Build

```bash
# Generate makefiles
./Utils/premake5 gmake

# Build
make -C Build/ config=release_x64 all -j$(nproc)

# Install data
./Prompts/linux-install-data.sh
```

**Available Configurations:**
- `release_x64` / `debug_x64` - 64-bit builds
- `release_x86` / `debug_x86` - 32-bit builds  
- `release_arm` / `debug_arm` - ARM 32-bit (experimental)
- `release_arm64` / `debug_arm64` - ARM 64-bit (experimental)

#### Method 3: Docker Build (Maximum Compatibility)

**Advantages:**
- Pre-configured build environment
- All dependencies included
- Same environment used for official builds
- Cross-compilation support

**Build Steps:**

```bash
# Pull Docker image
docker pull ghcr.io/multitheftauto/mtasa-blue-build:latest

# Navigate to source directory
cd /path/to/mtasa-blue

# Build (x86_64)
docker run --rm -v `pwd`:/build \
  ghcr.io/multitheftauto/mtasa-blue-build:latest \
  --arch=x64

# Build (x86 32-bit)
docker run --rm -v `pwd`:/build \
  ghcr.io/multitheftauto/mtasa-blue-build:latest \
  --arch=x86

# Build (ARM 64-bit)
docker run --rm -v `pwd`:/build \
  ghcr.io/multitheftauto/mtasa-blue-build:latest \
  --arch=arm64

# Debug build
docker run --rm -v `pwd`:/build \
  ghcr.io/multitheftauto/mtasa-blue-build:latest \
  --arch=x64 --config=debug
```

### Running the Server

```bash
cd Bin/server

# 64-bit
./mta-server64

# 32-bit
./mta-server

# With screen (keeps running after logout)
screen -S mtaserver ./mta-server64
```

**Install Resources:**
```bash
cd Bin/server/mods/deathmatch
git clone https://github.com/multitheftauto/mtasa-resources.git resources
```

---

## Troubleshooting

### Windows Issues

#### Cannot open include file 'afxres.h'

**Cause:** Missing MFC component  
**Solution:**
1. Open Visual Studio Installer
2. Click "Modify"
3. Select "Individual Components"
4. Enable: "C++ MFC for latest v143 build tools (x86 & x64)"
5. Click "Modify" to install

#### Cannot find d3dx9.h or d3dx9.lib

**Cause:** DirectX SDK not installed or environment variable not set  
**Solution:**
1. Verify DirectX SDK (August 2009) is installed
2. Restart computer after installation
3. Check environment variable: `echo %DXSDK_DIR%`
4. If empty, reinstall DirectX SDK and restart

**Manual Fix (if env var is set):**
1. Open Visual Studio
2. Right-click project → Properties
3. Configuration Properties → VC++ Directories
4. Include Directories → Add: `;$(DXSDK_DIR)Include;`
5. Library Directories → Add: `;$(DXSDK_DIR)Lib\x86;` (or `x64`)
6. Apply to both Debug and Release configurations

#### Error: netc_d.dll not found (CL38)

**Cause:** Data files not installed  
**Solution:**
```batch
Prompts\win-install-data.bat
```

If error persists:
```batch
# Delete the executable and rebuild
del Bin\Multi Theft Auto_d.exe
# Rebuild in Visual Studio
```

#### ERROR: Loading network library (net_d.dll) failed!

**Cause:** Data files not installed  
**Solution:**
```batch
Prompts\win-install-data.bat
```

#### CL17: Please ensure latest data files have been installed

**Cause:** Missing game data files  
**Solution:**
```batch
Prompts\win-install-data.bat
```

#### After cloning repository, project doesn't compile

**Cause:** Project files not generated  
**Solution:**
```batch
Prompts\win-create-projects.bat
```

#### Cannot open source file "xxx.h" after upgrading VS 2022

**Cause:** Outdated Windows SDK or cached VS files  
**Solution:**
1. Open Visual Studio Installer
2. Install latest Windows 10/11 SDK
3. Close Visual Studio
4. Delete `Build\.vs` folder
5. Restart Visual Studio

### Linux Issues

#### Missing libncurses or libmysqlclient

**Solution:**
```bash
# Debian/Ubuntu
sudo apt-get install libncurses-dev libmysqlclient-dev

# Fedora/RHEL
sudo dnf install ncurses-devel mysql-devel

# Arch
sudo pacman -S ncurses mysql
```

#### GCC version too old

**Cause:** GCC < 10 not supported  
**Solution:**
```bash
# Ubuntu/Debian
sudo apt-get install gcc-10 g++-10
export CC=gcc-10
export CXX=g++-10
```

#### Cross-compilation issues

**Solution:**  
Set environment variables for your target:
```bash
# Example for ARM64
export AR=aarch64-linux-gnu-ar
export CC=aarch64-linux-gnu-gcc
export CXX=aarch64-linux-gnu-g++
export GCC_PREFIX=aarch64-linux-gnu

./Prompts/linux-build.sh --arch=arm64
```

---

## Advanced Topics

### Build Configurations Explained

| Configuration | Optimization | Debug Symbols | Size | Use Case |
|--------------|--------------|---------------|------|----------|
| `Debug` | None | Full | Large | Development, debugging |
| `Release` | Maximum | Minimal | Small | Production, distribution |

**Debug Builds:**
- No optimization (`/Od`)
- Full debug symbols
- Runtime checks enabled
- Slower execution
- Larger file size
- Use for development

**Release Builds:**
- Maximum optimization (`/O2`)
- Minimal/no debug symbols
- No runtime checks
- Fast execution
- Smaller file size
- Use for production

### Build Platforms

| Platform | Architecture | Bits | Status |
|----------|-------------|------|--------|
| Win32 | x86 | 32-bit | Stable |
| x64 | x86_64 | 64-bit | Stable |
| ARM | ARM | 32-bit | Experimental |
| ARM64 | ARM64 | 64-bit | Experimental |

### Custom Build Options

#### Change Build Output Directory

Edit `premake5.lua`:
```lua
location "CustomBuildDir"
```

Then regenerate:
```batch
Prompts\win-create-projects.bat
```

#### Parallel Builds

**Visual Studio:**
- Tools → Options → Projects and Solutions → Build and Run
- Maximum parallel projects: Set to CPU cores

**MSBuild:**
```batch
msbuild Build\MTASA.sln /m:8
```

**Linux Make:**
```bash
make -C Build/ config=release_x64 -j8
```

### Continuous Integration

MTA uses GitHub Actions for CI/CD:
- [View Builds](https://github.com/multitheftauto/mtasa-blue/actions)
- [Workflow Configuration](https://github.com/multitheftauto/mtasa-blue/tree/master/.github/workflows)

### Development Resources

- [Coding Guidelines](https://wiki.multitheftauto.com/wiki/Coding_guidelines)
- [Contributing Guide](https://github.com/multitheftauto/mtasa-docs/blob/main/mtasa-blue/CONTRIBUTING.md)
- [API Documentation](https://wiki.multitheftauto.com/)
- [Nightly Builds](https://nightly.multitheftauto.com/)

---

## Need Help?

- **Discord:** [Join MTA Discord](https://discord.com/invite/mtasa)
- **Forum:** [Community Forum](https://community.multitheftauto.com/)
- **GitHub Issues:** [Report Bugs](https://github.com/multitheftauto/mtasa-blue/issues)
- **Wiki:** [Complete Documentation](https://wiki.multitheftauto.com/wiki/Compiling_MTASA)

---

**Last Updated:** November 2025  
**MTA Version:** 1.6+  
**Supported VS:** Visual Studio 2022
