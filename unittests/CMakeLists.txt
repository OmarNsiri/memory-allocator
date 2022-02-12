# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.22)

# Subdir config
set(This Test)
set(TestSources ./memallocTESTS.cc)

# Create test executable
add_executable(${This} memallocTESTS.cc ${LibSources})

target_include_directories(${This} PUBLIC "${LibHeaderDir}")
target_link_libraries(${This} gtest
#    MemoryAllocation
)