cmake_minimum_required(VERSION 3.14)
project(tagged_t LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing()

include_directories(include)

add_library(tagged_t INTERFACE)

target_include_directories(tagged_t
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")
foreach(TEST_SOURCE ${TEST_SOURCES})
    # Extract the test name from the file name
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_SOURCE})
    target_link_libraries(${TEST_NAME} tagged_t gtest gtest_main)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()


file(GLOB EXAMPLES_SOURCES "examples/*.cpp")
foreach(example_src ${EXAMPLES_SOURCES})
  get_filename_component(example_name ${example_src} NAME_WE)
  add_executable(${example_name} ${example_src})
  target_link_libraries(${example_name} PRIVATE tagged_t)
endforeach()
