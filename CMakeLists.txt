cmake_minimum_required(VERSION 3.16)

# Conan's toolchain sets CMAKE_GENERATOR_PLATFORM for MSVC targets.
# Non-Visual-Studio generators (Ninja, etc.) don't support platform
# specification, so clear any stale cached value before project().
if(NOT CMAKE_GENERATOR MATCHES "Visual Studio")
    unset(CMAKE_GENERATOR_PLATFORM CACHE)
endif()

project(cicd-0112358 VERSION 1.0.0 LANGUAGES CXX)

# ---- Conan Integration -------------------------------------------------------
set(_conan_output_dir "${CMAKE_BINARY_DIR}/conan")

get_property(_is_multi_config GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if(_is_multi_config)
    set(_conan_build_types Debug Release MinSizeRel RelWithDebInfo)
else()
    if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    endif()
    set(_conan_build_types "${CMAKE_BUILD_TYPE}")
endif()

foreach(_bt IN LISTS _conan_build_types)
    set(_conan_stamp "${_conan_output_dir}/.conan_${_bt}_done")
    if(NOT EXISTS "${_conan_stamp}" OR
       "${CMAKE_SOURCE_DIR}/conanfile.txt" IS_NEWER_THAN "${_conan_stamp}")
        message(STATUS "Conan: installing dependencies for ${_bt}...")
        execute_process(
            COMMAND conan install "${CMAKE_SOURCE_DIR}"
                    --output-folder "${_conan_output_dir}"
                    --build=missing
                    -s build_type=${_bt}
            RESULT_VARIABLE _conan_result
        )
        if(NOT _conan_result EQUAL 0)
            message(FATAL_ERROR
                "conan install failed for build_type=${_bt}. "
                "Ensure Conan 2 is installed and available in PATH.")
        endif()
        file(TOUCH "${_conan_stamp}")
        # Conan updates CMakeUserPresets.json to advertise its own presets, which
        # appear as duplicate configurations in VS alongside our own presets.
        # We load the toolchain directly, so those generated presets are not needed.
        file(WRITE "${CMAKE_SOURCE_DIR}/CMakeUserPresets.json"
            "{\n    \"version\": 4,\n    \"vendor\": { \"conan\": {} }\n}\n")
    endif()
endforeach()

include("${_conan_output_dir}/conan_toolchain.cmake")
# Conan's MSVC toolchain writes CMAKE_GENERATOR_PLATFORM / CMAKE_GENERATOR_TOOLSET
# to cache; clear them for non-Visual-Studio generators so they don't break future
# Ninja reconfigures (e.g. VS IDE's built-in x64-debug config).
if(NOT CMAKE_GENERATOR MATCHES "Visual Studio")
    unset(CMAKE_GENERATOR_PLATFORM CACHE)
    unset(CMAKE_GENERATOR_TOOLSET CACHE)
endif()

# ---- C++ Standard ------------------------------------------------------------
# Set after toolchain inclusion to explicitly override Conan's profile default.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---- Build Targets -----------------------------------------------------------

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

# ---- Tests -------------------------------------------------------------------
find_package(GTest REQUIRED)
enable_testing()

add_executable(test_fibonacci tests/test_fibonacci.cpp)
target_link_libraries(test_fibonacci PRIVATE fibonacci GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_fibonacci)
