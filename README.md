# HLouge PhysicsEngine

![Version](https://img.shields.io/badge/version-1.0.1-blue.svg)
![Language](https://img.shields.io/badge/language-C-orange.svg)
![Build](https://img.shields.io/badge/build-CMake-green.svg)
![License](https://img.shields.io/badge/license-MIT-lightgrey.svg)

A lightweight 2D physics engine written in **C**, built with **CMake**, and utilizing **SDL2** for graphics rendering. 
Currently features a multi-particle fireworks simulation with gravity, collisions, and visual trails.

> *This project was created in parallel with assignments from the CS Major at **École des Mines de Saint-Étienne**.*

# Features

* **Particle System**: Simulation of 100+ concurrent particles (Fireworks demo).
* **Physics**: Gravity implementation, momentum conservation, and boundary collisions (floor and walls).
* **Visual Effects**: Motion trails for each particle using alpha blending.
* **Data-Driven**: Key parameters (Gravity, Dimensions, Start Position) are loadable via a `config.txt` file.
* **Robust Build**: Fully managed by **CMake** with **Cppcheck** static analysis integration.
* **Packaging**: Automatic generation of `.zip` or `.tar.gz` release packages via CPack.

# Prerequisites

Before compiling, ensure you have the following installed:

* **CMake** (version 3.10+)
* **GCC** or any standard C compiler
* **Make**
* **SDL2 Library** (Development headers)
* **Cppcheck** (Optional, for static analysis)

# Installing Dependencies (Debian/Ubuntu)

```bash
sudo apt-get update
sudo apt-get install build-essential cmake libsdl2-dev cppcheck
```

# Build & Run

1. Clone the repository


```bash
git clone [https://github.com/hlouge/PHYSICS_ENGINE.git](https://github.com/hlouge/PHYSICS_ENGINE.git)
cd PHYSICS_ENGINE
```

2. Build the project

We use an "out-of-source" build to keep directories clean.

```bash
# Generate build files in 'build/' directory
cmake -B build

# Compile the executable
cmake --build build
```

3. Run the Simulation

The executable and the config.txt are automatically placed in the build/ directory.

```bash
./build/Engine
```
**Configuration**

You can tweak the simulation without recompiling by editing the build/config.txt file:
Ini, TOML

POS_X 400.0     # Initial X source position
POS_Y 300.0     # Initial Y source position
WIN_W 800       # Window Width
WIN_H 600       # Window Height
GRAVITY 9.81    # Gravity force
RADIUS 4        # Particle radius

Press SPACE during the simulation to restart the explosion.

**Packaging**

To distribute the engine as a standalone archive:

```bash
cd build
cpack
```

This will generate a portable archive (e.g., Physics_Engine-1.0.0-Linux.zip) containing the binary and configuration.

**Static Code Analysis**

To ensure code quality and prevent memory leaks, this project integrates **Cppcheck**. The analysis is automatically hooked into the CMake build system.

### Prerequisites
You need to have `cppcheck` installed on your machine.
```bash
sudo apt-get install cppcheck
```
How it works

Cppcheck runs automatically every time you compile the project. If it detects any bugs, undefined behaviors, or style issues, it will report them directly in your terminal output during the build process.
Bash

# The analysis runs during this step:
```bash
cmake --build build
```
Note: If Cppcheck is not found on your system, CMake will simply skip this step without failing.

**Author**

HLouge Student at École des Mines de Saint-Étienne.
