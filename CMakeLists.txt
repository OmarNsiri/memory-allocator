# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.22)

# Project config
project(MemAlloc VERSION 1.0.0)
set(This MemoryAllocation)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

# Set filesystem variables
set(LibSourceDir "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(LibHeaderDir "${CMAKE_CURRENT_SOURCE_DIR}/inc")

file(GLOB LibSources "${LibSourceDir}/*")
file(GLOB LibHeaders "${LibHeaderDir}/*")

# Importing modules
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)


# Add Cmake subdirectories
add_subdirectory(unittests)

# Add libraries
add_library(${This} SHARED "${LibSources}")
target_include_directories(${This} PUBLIC "${LibHeaderDir}")