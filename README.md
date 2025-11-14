**HLouge PhysicsEngine**

Version 1.0.0

A simple 2D physics engine in C, built with CMake and using SDL2 for graphics rendering.
This project was created in parralel of assignements from Ecole des Mines Saint-Etienne CS Major.

**Features**

Simulation of a physical object (circle) with gravity.
Collision and bounce on the window floor.
Simple graphics rendering via the SDL2 library.
Project fully managed by CMake (compilation, dependency management, packaging).

**Prerequisites**

Before compiling, you must have the following tools installed on your system:

    - cmake (version 3.10 or higher)

    - A C compiler (e.g., gcc)

    - make 

    - The SDL2 library (development version)

**Installing Prerequisites**

On Debian/Ubuntu:

sudo apt-get update
sudo apt-get install build-essential cmake libsdl2-dev

Usage Guide

1. How to Build

# 1. Clone the repository (if not already done)
> git clone [git clone https://github.com.hlouge/PHYSICS_ENGINE]
> cd PhysicsEngine

# 2. Create a build directory and configure the project

>cmake -B build

# 3. Launch the compilation

>cmake --build build


At the end of this process, an executable named Engine will be created in the build/ directory.

2. How to Run

Once the build is successful, you can run the simulation:

./build/Engine

4. Packaging

This project is configured with CPack to generate installation packages (.zip or .tar.gz).

# 1. Make sure you have compiled the project (see step 1)
# 2. Change to the build directory
>cd build

# 3. Run CPack
>cpack

CPack will generate an archive (e.g., PhysicsEngine-1.0.0-Linux.zip) in the build/ directory. This archive contains the Engine executable, ready for distribution.
