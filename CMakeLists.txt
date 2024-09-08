cmake_minimum_required(VERSION 3.10)
project(TemplateProject)

set(CMAKE_CXX_STANDARD 11)

# Add the main source file
add_executable(main src/main.cpp)

# Add Google Test
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add the test source file
add_executable(test_main tests/test_main.cpp)

# Link Google Test and pthread
target_link_libraries(test_main ${GTEST_LIBRARIES} pthread)

# Add a test
add_test(NAME test_main COMMAND test_main)