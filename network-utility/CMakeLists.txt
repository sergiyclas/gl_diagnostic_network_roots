cmake_minimum_required(VERSION 3.10)

# Назва проекту
project(NetworkUtility)

# Встановлення стандарту C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Додавання директорій з заголовковими файлами
include_directories(include src/types src/utils)

# Додавання основного виконуваного файлу
add_executable(network-utility
    src/main.cpp
    src/traceroute.cpp
    src/utils/network_utils.cpp
)

# Додавання тестів
enable_testing()
add_executable(test_network_utility
    tests/test_main.cpp
    tests/test_traceroute.cpp
    tests/test_network_utils.cpp
    src/traceroute.cpp
    src/utils/network_utils.cpp
)

# Підключення бібліотеки Google Test
set(GTEST_INCLUDE_DIRS "C:/My_deals/Linux/GL/diagnostic_network_manager/googletest/googletest/include")
set(GTEST_LIBRARIES "C:/My_deals/Linux/GL/diagnostic_network_manager/googletest/build/lib/Release/gtest.lib")
set(GTEST_MAIN_LIBRARIES "C:/My_deals/Linux/GL/diagnostic_network_manager/googletest/build/lib/Release/gtest_main.lib")

include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(test_network_utility ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})

# Додавання тестів до CTest
add_test(NAME NetworkUtilsTest COMMAND test_network_utility)