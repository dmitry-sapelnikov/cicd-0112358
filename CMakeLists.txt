# Project settings
cmake_minimum_required(VERSION 3.21)
project(cicd-0112358 VERSION 1.0.0 LANGUAGES CXX)

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Conan package paths – add out/conan so find_package locates Conan-installed
# dependencies without requiring CMAKE_TOOLCHAIN_FILE to be set externally.
set(_conan_dir "${CMAKE_CURRENT_SOURCE_DIR}/out/conan")
if(IS_DIRECTORY "${_conan_dir}")
    list(PREPEND CMAKE_PREFIX_PATH "${_conan_dir}")
    list(PREPEND CMAKE_MODULE_PATH "${_conan_dir}")
endif()
unset(_conan_dir)

# Build Targets

add_library(fibonacci STATIC
    src/fibonacci.cpp
)

target_include_directories(fibonacci PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

add_executable(fibonacci_hello_world
    examples/fibonacci_hello_world/main.cpp
)

target_link_libraries(fibonacci_hello_world PRIVATE fibonacci)

# Tests
option(BUILD_TESTING "Build the test suite (requires Conan-installed GTest)" OFF)
if(BUILD_TESTING)
    include(CTest)
    find_package(GTest REQUIRED)
    add_executable(test_fibonacci tests/test_fibonacci.cpp)
    target_link_libraries(test_fibonacci PRIVATE fibonacci GTest::gtest_main)
    include(GoogleTest)
    gtest_discover_tests(test_fibonacci)
endif()
