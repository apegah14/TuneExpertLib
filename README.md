# Tune Expert Data Parser

## Purpose
The purpose of the Tune Expert Data Parser is to expand the functions of the N1231B Laser Interferometer Board API from Keysight. The API calls work by storing board data directly into memory addresses instead of returning the data as primative types (ints/floats/etc.). This leads to some issues when trying to use these provided libraries with applications such as Matlab. In addition, it is generally easier for programmers, some of which may not be too familiar with working with C/C++ pointers, to implement functions that return primartive data types.

Therefor, this cross-platform library was created to solve this issue by having a number of functions that neatly open/setup the board, as well as return position and velocity data in easy to parse formats.

## Compiling
### Dependencies
There are a few dependencies that should be noted:
- A C/C++ compiler (we recommend just installing build-essentials for Linux and MinGW for Windows)
- CMake
- make (Linux)
- Ninja (Linux)
- N1231B Driver (from Keysight)

A CMakeLists.txt file is include in the project with the proper, in addition to all libraries necessary for compilation and expansion of this project.

`git clone ()
cd ()
cmake
make`

CMake presets can also be used if prefered

## Issues
Currently the only way this library can be compiled to work with Matlab on Windows is through the use of gcc. MSVC (from Visual Studio) has some major issues that we have not been able to solve when attempting to load the library in Matlab.