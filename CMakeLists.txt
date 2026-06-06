cmake_minimum_required(VERSION 3.10)

project(physics_sandbox)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)

add_executable(physics_sandbox src/main.cpp)

target_include_directories(physics_sandbox PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(physics_sandbox PRIVATE ${SDL2_LIBRARIES})