# CMakeList.txt : CMake project for TuneExpertDataLib, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("TuneExpertData")

include_directories("${CMAKE_SOURCE_DIR}/include")
# Add source to this project's executable.
add_library (TuneExpertData SHARED "src/TuneExpertData.c" "src/TuneExpertData.h")
if (WIN32)
	target_link_libraries(TuneExpertData "${CMAKE_SOURCE_DIR}/shared/N1231B.dll")
endif (WIN32)
if (UNIX)
	target_link_libraries(TuneExpertData "${CMAKE_SOURCE_DIR}/shared/libN1231B.so")
	target_link_libraries(TuneExpertData "${CMAKE_SOURCE_DIR}/shared/libPlxApi.so")
endif (UNIX)