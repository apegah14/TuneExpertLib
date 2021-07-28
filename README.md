# Tune Expert Data Parser

## Purpose
The purpose of the Tune Expert Data Parser is to expand the functions of the N1231B Laser Interferometer Board API from Keysight. The API calls work by storing board data directly into memory addresses instead of returning the data as primative types (ints/floats/etc.). This leads to some issues when trying to use these provided libraries with applications such as Matlab. In addition, it is generally easier for programmers, some of which may not be too familiar with working with C/C++ pointers, to implement functions that return primartive data types.

Therefor, this cross-platform library was created to solve this issue by having a number of functions that neatly open/setup the board, as well as return position and velocity data in easy to parse formats.

## Compiling
### Dependencies
There are a few dependencies that should be noted:
- A C/C++ compiler (we recommend just installing build-essentials for Linux and MinGW64 for Windows)
- CMake
- make (Linux)
- Ninja (Linux)
- N1231B Driver (from Keysight)

A CMakeLists.txt file is include in the project with the proper, in addition to all libraries necessary for compilation and expansion of this project.

### Linux
`git clone https://github.com/apegah14/TuneExpertLib`

`cd TuneExpertLib`

`cmake`

`make`

CMake presets can also be used if prefered

### VSCode
This is generally the easiest way to compile this library on both Windows and Linux. The CMake extension is required to build it within VSCode and a build folder will be created with the library as well as make files nicely packaged.

## Issues
Currently the only way this library can be compiled to work with Matlab on Windows is through the use of gcc. MSVC (from Visual Studio) has some major issues that we have not been able to solve when attempting to load the library in Matlab.

Please ensure that a 64-bit compiler is being used as well