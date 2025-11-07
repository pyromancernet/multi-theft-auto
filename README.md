## Multi Theft Auto: San Andreas

[![Build Status](https://github.com/multitheftauto/mtasa-blue/workflows/Build/badge.svg?event=push&branch=master)](https://github.com/multitheftauto/mtasa-blue/actions?query=branch%3Amaster+event%3Apush) [![Unique servers online](https://img.shields.io/endpoint?url=https%3A%2F%2Fmultitheftauto.com%2Fapi%2Fservers-shields.io.json)](https://community.multitheftauto.com/index.php?p=servers) [![Unique players online](https://img.shields.io/endpoint?url=https%3A%2F%2Fmultitheftauto.com%2Fapi%2Fplayers-shields.io.json)](https://multitheftauto.com) [![Unique players last 24 hours](https://img.shields.io/endpoint?url=https%3A%2F%2Fmultitheftauto.com%2Fapi%2Funique-players-shields.io.json)](https://multitheftauto.com) [![Discord](https://img.shields.io/discord/278474088903606273?label=discord&logo=discord)](https://discord.com/invite/mtasa) [![Crowdin](https://badges.crowdin.net/e/f5dba7b9aa6594139af737c85d81d3aa/localized.svg)](https://multitheftauto.crowdin.com/multitheftauto)

[Multi Theft Auto](https://www.multitheftauto.com/) (MTA) is a software project that adds network play functionality to Rockstar North's Grand Theft Auto game series, in which this functionality is not originally found. It is a unique modification that incorporates an extendable network play element into a proprietary commercial single-player PC game.

---

## 📑 Table of Contents

- [Introduction](#introduction)
- [Gameplay Content](#gameplay-content)
- [Development](#development)
  - [Build Instructions](#build-instructions)
    - [Windows](#windows)
    - [GNU/Linux](#gnulinux)
  - [Development Workflow](#development-workflow)
- [Resources and Support](#resources-and-support)
- [License](#license)

---

## Introduction

Multi Theft Auto is based on code injection and hooking techniques whereby the game is manipulated without altering any original files supplied with the game. The software functions as a game engine that installs itself as an extension of the original game, adding core functionality such as networking and GUI rendering while exposing the original game's engine functionality through a scripting language.

Originally founded back in early 2003 as an experimental piece of C/C++ software, Multi Theft Auto has since grown into an advanced multiplayer platform for gamers and third-party developers. Our software provides a minimal sandbox style gameplay that can be extended through the Lua scripting language in many ways, allowing servers to run custom created game modes with custom content for up to hundreds of online players.

Formerly a closed-source project, we have migrated to open-source to encourage other developers to contribute as well as showing insight into our project's source code and design for educational reasons.

Multi Theft Auto is built upon the "Blue" concept that implements a game engine framework. Since the class design of our game framework is based upon Grand Theft Auto's design, we are able to insert our code into the original game. The game is then heavily extended by providing new game functionality (including tweaks and crash fixes) as well as a completely new graphical interface, networking and scripting component.

## Gameplay content

By default, Multi Theft Auto provides the minimal sandbox style gameplay of Grand Theft Auto. The gameplay can be heavily extended through the use of the Lua scripting language that has been embedded in the client and server software. Both the server hosting the game, as well as the client playing the game are capable of running and synchronizing Lua scripts. These scripts are layered on top of Multi Theft Auto's game framework that consists of many classes and functions so that the game can be adjusted in virtually any possible way.

All gameplay content such as Lua scripts, images, sounds, custom models or textures is grouped into a "resource". This resource is nothing more than an archive (containing the content) and a metadata file describing the content and any extra information (such as dependencies on other resources).

Using a framework based on resources has a number of advantages. It allows content to be easily transferred to clients and servers. Another advantage is that we can provide a way to import and export scripting functionality in a resource. For example, different resources can import (often basic) functionality from one or more common resources. These will then be automatically downloaded and started. Another feature worth mentioning is that server administrators can control the access to specific resources by assigning a number of different user rights to them.

## Development

Multi Theft Auto is an open-source project welcoming contributions from developers worldwide. Our project's code repository is hosted on [GitHub](https://github.com/multitheftauto/mtasa-blue/).

**Quick Links:**
- 📖 [Complete Build Guide](./BUILDING.md) - Comprehensive build instructions and troubleshooting
- 📋 [Build Scripts Documentation](./Prompts/README.md) - Detailed script usage
- 📝 [Coding Guidelines](https://github.com/multitheftauto/mtasa-docs/blob/main/mtasa-blue/CONTRIBUTING.md) - Contribution standards
- 🌙 [Nightly Builds](https://nightly.multitheftauto.com/) - Latest development builds
- 🎯 [Milestones](https://github.com/multitheftauto/mtasa-blue/milestones) - Development roadmap

### Build Instructions

> � **For complete build instructions, troubleshooting, and advanced topics, see [BUILDING.md](./BUILDING.md)**

> �💡 **Tip:** All build scripts are located in the `Prompts/` directory. See [Prompts/README.md](./Prompts/README.md) for detailed script documentation.

#### Windows

##### Prerequisites

**Required Software:**
- [Visual Studio 2022](https://visualstudio.microsoft.com/vs/) (Community Edition is free) with:
  - ✅ Desktop development with C++
  - ✅ Optional component: *C++ MFC for latest v143 build tools (x86 & x64)*
- [Microsoft DirectX SDK (August 2009)](https://wiki.multitheftauto.com/wiki/Compiling_MTASA#Microsoft_DirectX_SDK)
  - [Mirror 1 (archive.org)](https://archive.org/download/dxsdk_aug09/DXSDK_Aug09.exe)
  - [Mirror 2 (mega.nz)](https://mega.nz/file/pQJCiAJY#jBcYT6ZP4DMBpnm12BLRto9EQ-RjjpP3BWkSPanpvLI)
  - ⚠️ **Important:** Restart your computer after installing DirectX SDK

**Optional:**
- [Git for Windows](https://git-scm.com/download/win) (recommended for contributors)

##### Quick Build (Automated)

```batch
# Build everything automatically (Release, Win32)
Prompts\win-build.bat

# Build with specific configuration
Prompts\win-build.bat Debug x64
Prompts\win-build.bat Release Win32
```

The automated script will:
1. Generate Visual Studio solution files
2. Download and install dependencies (CEF, Unifont, Discord RPC)
3. Compile the project using MSBuild
4. Output binaries to `Bin/` directory

After building, install data files:
```batch
Prompts\win-install-data.bat
```

##### Manual Build (Step by Step)

1. **Generate project files:**
   ```batch
   Prompts\win-create-projects.bat
   ```
   This installs dependencies (CEF, Unifont, Discord RPC) and generates Visual Studio solution files.

2. **Open Visual Studio:**
   - Open `Build/MTASA.sln`
   - Select configuration: `Debug` or `Release`
   - Select platform: `Win32`, `x64`, `ARM`, or `ARM64`
   - Press `F7` or `Build > Build Solution`

3. **Install data files:**
   ```batch
   Prompts\win-install-data.bat
   ```
   This copies essential files to `Bin/` and optionally installs [official resources](https://github.com/multitheftauto/mtasa-resources).

##### Running After Build

**Client:**
- Navigate to `Bin/` directory
- Run `Multi Theft Auto.exe` (Release) or `Multi Theft Auto_d.exe` (Debug)

**Server:**
- Navigate to `Bin/server/` directory
- Run `MTA Server.exe` (Release) or `MTA Server_d.exe` (Debug)
- Server requires [official resources](https://github.com/multitheftauto/mtasa-resources) to be installed in `Bin/server/mods/deathmatch/resources/`

##### Common Build Configurations

| Configuration | Platform | Use Case |
|--------------|----------|----------|
| `Release` | `Win32` | Standard 32-bit build |
| `Release` | `x64` | 64-bit build (recommended) |
| `Debug` | `Win32` | Development with debugging symbols |
| `Debug` | `x64` | 64-bit development build |

##### Troubleshooting

**Error: Cannot open include file 'afxres.h'**
- Solution: Install "C++ MFC for latest v143 build tools" via Visual Studio Installer

**Error: Cannot find d3dx9.h**
- Solution: Install DirectX SDK and restart your computer
- Verify `DXSDK_DIR` environment variable is set

**Error: netc_d.dll not found**
- Solution: Run `Prompts\win-install-data.bat`

**Error: After cloning, project doesn't compile**
- Solution: Run `Prompts\win-create-projects.bat` to generate solution files

Visit the wiki article ["Compiling MTASA"](https://wiki.multitheftauto.com/wiki/Compiling_MTASA) for additional information and error troubleshooting.

#### GNU/Linux

##### Prerequisites

You can build MTA:SA server on GNU/Linux distributions for **x86**, **x86_64**, **armhf**, and **arm64** architectures. 

> ⚠️ **Note:** ARM architectures (armhf/arm64) are currently **experimental** - they may be unstable and crash randomly.  
> ✅ **Officially Supported:** Building from x86_64, including cross-compilation for other architectures.

**Build Dependencies:**

*Always check `Utils/docker/Dockerfile` for the most up-to-date dependencies.*

- `make`
- GNU GCC compiler (version 10 or newer)
- `libncurses-dev`
- `libmysqlclient-dev`

##### Quick Build (Automated Script)

> ⚠️ **Warning:** This script deletes `Build/` and `Bin/` directories for a clean build.

```bash
# Build with default settings (x64, release)
./Prompts/linux-build.sh

# Build with specific configuration
./Prompts/linux-build.sh --arch=x64 --config=release --cores=8
./Prompts/linux-build.sh --arch=x86 --config=debug
./Prompts/linux-build.sh --arch=arm64 --config=release

# Install data files (optional)
./Prompts/linux-install-data.sh
```

**Script Parameters:**
- `--arch`: Build architecture (`x86`, `x64`, `arm`, `arm64`) - defaults to `x64`
- `--config`: Build configuration (`debug`, `release`) - defaults to `release`
- `--cores`: Number of parallel build jobs - defaults to CPU core count

**Cross-Compilation:**
Set environment variables for cross-compilation:
- `AR` - Archiver tool
- `CC` - C compiler
- `CXX` - C++ compiler
- `GCC_PREFIX` - Compiler prefix

See `Utils/docker/Dockerfile` for examples.

##### Manual Build

```bash
# Generate makefiles
./Utils/premake5 gmake

# Build specific configuration
make -C Build/ config=release_x64 all

# Or build debug for different architecture
make -C Build/ config=debug_x86 all
```

**Available Build Configurations:**
- `release_x64` - 64-bit release build
- `release_x86` - 32-bit release build
- `release_arm` - ARM 32-bit release build
- `release_arm64` - ARM 64-bit release build
- `debug_x64` - 64-bit debug build
- `debug_x86` - 32-bit debug build
- `debug_arm` - ARM 32-bit debug build
- `debug_arm64` - ARM 64-bit debug build

##### Docker Build Environment

For maximum compatibility and easy dependency management, use our official Docker build environment.

**Pull Docker Image:**
```bash
docker pull ghcr.io/multitheftauto/mtasa-blue-build:latest
```

**Build with Docker:**

```bash
# Navigate to mtasa-blue directory
cd /path/to/mtasa-blue

# x86_64 build (default)
docker run --rm -v `pwd`:/build ghcr.io/multitheftauto/mtasa-blue-build:latest --arch=x64

# x86 (32-bit) build
docker run --rm -v `pwd`:/build ghcr.io/multitheftauto/mtasa-blue-build:latest --arch=x86

# ARM 32-bit build (experimental)
docker run --rm -v `pwd`:/build ghcr.io/multitheftauto/mtasa-blue-build:latest --arch=arm

# ARM 64-bit build (experimental)
docker run --rm -v `pwd`:/build ghcr.io/multitheftauto/mtasa-blue-build:latest --arch=arm64

# Debug build (add --config=debug)
docker run --rm -v `pwd`:/build ghcr.io/multitheftauto/mtasa-blue-build:latest --arch=x64 --config=debug
```

Compiled binaries will be available in the `Bin/` directory.

##### Running the Server

```bash
# Navigate to server directory
cd Bin/server

# Run the server
./mta-server64  # or ./mta-server for 32-bit
```

**Installing Resources:**
Download [official resources](https://github.com/multitheftauto/mtasa-resources) and extract to `Bin/server/mods/deathmatch/resources/`

### Development Workflow

#### Debugging

**Windows - Visual Studio Debugging:**

1. **Set Build Configuration:**
   - Switch to `Debug` configuration in Visual Studio
   - Select platform (`Win32` or `x64`)
   - Build the solution (`F7`)

2. **Launch with Debugger:**
   - Press `F5` or click "Local Windows Debugger"
   - Or manually run the executable and attach debugger

3. **Enable Breakpoints in Game:**
   - Start MTA in Visual Studio debugger
   - Attach debugger to `gta_sa.exe` process:
     - Press `Ctrl + Alt + P` in Visual Studio
     - Find and select `gta_sa.exe`
     - Click "Attach"
   - Now breakpoints will work for client-side code

4. **Extend Timeout Duration:**
   - Breakpoints freeze the client, causing server timeout kicks
   - Create file: `Bin/server/timeout.longtime`
   - Add timeout value in seconds (e.g., `3600` for 1 hour)
   - Empty file defaults to 120 seconds

**Recommended Tools:**
- [ReAttach Extension](https://marketplace.visualstudio.com/items?itemName=ErlandR.ReAttach) - Automatically re-attach debugger to `gta_sa.exe` when launching MTA

**Linux - GDB Debugging:**

```bash
# Build debug configuration
./Prompts/linux-build.sh --config=debug

# Run with GDB
cd Bin/server
gdb ./mta-server64

# In GDB
(gdb) run
(gdb) break SomeFunction
(gdb) continue
```

#### Adding New Source Files

When adding new C++ source files (`.cpp`, `.h`):

1. **Add files to your workspace**
2. **Regenerate project files:**
   ```batch
   # Windows
   Prompts\win-create-projects.bat
   ```
   ```bash
   # Linux
   ./Utils/premake5 gmake
   ```
3. **Rebuild the solution**

> 💡 **Why?** MTA uses Premake5 to generate project files. New source files must be detected by Premake5 to be included in the build.

#### Code Contribution Guidelines

Before contributing, please review:
- [Contributors Guide and Coding Guidelines](https://github.com/multitheftauto/mtasa-docs/blob/main/mtasa-blue/CONTRIBUTING.md)
- [Coding Guidelines](https://wiki.multitheftauto.com/wiki/Coding_guidelines)

**Contribution Workflow:**
1. Fork the [multitheftauto/mtasa-blue](https://github.com/multitheftauto/mtasa-blue/) repository
2. Clone your fork locally
3. Create a feature branch
4. Make your changes following coding guidelines
5. Test thoroughly (both Debug and Release builds)
6. Commit with clear, descriptive messages
7. Push to your fork
8. Open a Pull Request

**Testing Your Changes:**
- Always test in both `Debug` and `Release` configurations
- Test on different platforms if possible (Win32/x64)
- Ensure no new compiler warnings
- Check for memory leaks in Debug builds
- Verify functionality with official resources

#### Build Scripts Location

All build automation scripts are in the `Prompts/` directory:

**Windows:**
- `win-create-projects.bat` - Generate VS solution files
- `win-build.bat` - Automated build with MSBuild
- `win-install-data.bat` - Install data files and resources

**Linux:**
- `linux-build.sh` - Automated build script
- `linux-install-data.sh` - Install data files and resources

**Cross-Platform:**
- `wine-build.sh` - Build Windows version using Wine

See [Prompts/README.md](./Prompts/README.md) for detailed script documentation.

### Resources and Support

**Official Resources:**
- [Nightly Builds](https://nightly.multitheftauto.com/) - Latest development builds
- [Wiki Documentation](https://wiki.multitheftauto.com/) - Complete documentation
- [Scripting Reference](https://wiki.multitheftauto.com/wiki/Main_Page) - Lua scripting API
- [Official Resources](https://github.com/multitheftauto/mtasa-resources) - Default game resources

**Community:**
- [Discord Server](https://discord.com/invite/mtasa) - Community chat and support
- [GitHub Issues](https://github.com/multitheftauto/mtasa-blue/issues) - Bug reports and feature requests
- [Milestones](https://github.com/multitheftauto/mtasa-blue/milestones) - Development roadmap
- [Community Forum](https://community.multitheftauto.com/) - Forum discussions

**Build Status:**
- [GitHub Actions](https://github.com/multitheftauto/mtasa-blue/actions) - CI/CD build status
- [Crowdin Translation](https://multitheftauto.crowdin.com/multitheftauto) - Help translate MTA

### Premake FAQ

#### How to add new C++ source files?

Execute `Prompts/win-create-projects.bat`

## License

Unless otherwise specified, all source code hosted on this repository is licensed under the GPLv3 license. See the [LICENSE](./LICENSE) file for more details.

Grand Theft Auto and all related trademarks are © Rockstar North 1997–2025.