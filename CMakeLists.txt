cmake_minimum_required(VERSION 3.14)
project(tagged_t LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable testing
enable_testing()

# Add the include directory for your project
include_directories(include)

# Add source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create a library from your source files
add_library(tagged_t STATIC ${SOURCES})
target_include_directories(tagged_t PUBLIC include)

# Fetch Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
# Download and build Google Test
FetchContent_MakeAvailable(googletest)

# Link Google Test to test executables
file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")
foreach(TEST_SOURCE ${TEST_SOURCES})
    # Extract the test name from the file name
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_SOURCE})
    target_link_libraries(${TEST_NAME} tagged_t gtest gtest_main)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()

