# Physics Sandbox

A custom 2D particle simulation and physics engine built from scratch in C++23. 

## Dependencies

This project requires a compiler that supports **C++23**, along with **CMake** and **SDL2** for windowing and rendering. 

If you are on a Debian/Ubuntu-based Linux distribution, you can install all necessary build tools and libraries via `apt`:

```bash
sudo apt update
sudo apt install build-essential cmake pkg-config libsdl2-dev
```

## Build Instructions

This project is configured for an out-of-source CMake build. Run the following commands from the root directory of the project to configure and compile:

```bash
# 1. Generate the build system inside a new 'build' folder
cmake -B build

# 2. Compile the project
cmake --build build
```

## Running the Simulation

After a successful compilation, the executable will be located inside your `build` directory. You can run it directly from the root folder:

```bash
./build/physics_sandbox
```