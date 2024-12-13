#!/bin/bash

# Setup for building Playloom Engine

echo "Setting up build environment..."

# Install dependencies
sudo apt update
sudo apt install -y build-essential cmake

# Create build directory
mkdir build
cd build

# Configure build with CMake
cmake ..

# Build the project
make

echo "Build setup complete!"