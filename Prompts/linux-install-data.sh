#!/bin/bash

# Change to repository root directory
cd "$(dirname "$0")/.."

# Find premake binary location
if [ "$(uname)" == "Darwin" ]; then
    PREMAKE5=Utils/premake5-macos
else
    PREMAKE5=Utils/premake5
fi

# Install data files
$PREMAKE5 install_data