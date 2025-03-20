cmake_minimum_required(VERSION 3.10)

# Project name
project(NetworkUtility)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include src/types src/utils)

# Add executable
add_executable(network-utility
    src/main.cpp
    src/traceroute.cpp
    src/utils/network_utils.cpp
)

# Add tests
enable_testing()
add_executable(test_network_utility
    tests/test_main.cpp
    tests/test_traceroute.cpp
    tests/test_network_utils.cpp
    src/traceroute.cpp
    src/utils/network_utils.cpp
)

# Link Google Test library
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(test_network_utility ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)

# Add tests to CTest
add_test(NAME NetworkUtilsTest COMMAND test_network_utility)