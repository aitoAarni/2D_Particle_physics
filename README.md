sudo apt update
sudo apt install build-essential cmake libsdl2-dev

# 1. Create a build directory and navigate into it
mkdir build
cd build

# 2. Generate the build files
cmake ..

# 3. Compile the project
make

