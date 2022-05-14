cmake_minimum_required(VERSION 3.16)
# Set the project name and language
project(myprojectqt_starter_template
  VERSION 0.0.1
  DESCRIPTION ""
  HOMEPAGE_URL "%%myurl%%"
  LANGUAGES CXX C)


# Not ideal to use this global variable, but necessary to make sure
# that tooling and projects use the same version
set(CMAKE_CXX_STANDARD 20)

# strongly encouraged to enable this globally to avoid conflicts between
# -Wpedantic being enabled and -std=c++20 and -std=gnu++20 for example
# when compiling with PCH enabled
set(CMAKE_CXX_EXTENSIONS OFF)

# Note: by default ENABLE_DEVELOPER_MODE is True
# This means that all analysis (sanitizers, static analysis)
# is enabled and all warnings are treated as errors
# This CMakeLists.txt in the project's root is reserved for developers.
# Project users (who want to install / use this library but not contribute to it)
# should build the project from src/ instead (cmake -S ./src -B ./build)
set(ENABLE_DEVELOPER_MODE
    TRUE
    CACHE BOOL "Enable 'developer mode'")

# Add project_options v0.21.1 from aminya's github repository:
# https://github.com/aminya/project_options
include(FetchContent)
FetchContent_Declare(_project_options
                     URL https://github.com/aminya/project_options/archive/refs/tags/v0.21.1.zip)
FetchContent_MakeAvailable(_project_options)
include(${_project_options_SOURCE_DIR}/Index.cmake)

# Handle multi config builds
get_property(BUILDING_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if(BUILDING_MULTI_CONFIG)
  if(NOT CMAKE_BUILD_TYPE)
    message(TRACE "Setting up multi-config build types")
    set(CMAKE_CONFIGURATION_TYPES
        Debug
        Release
        RelWithDebInfo
        MinSizeRel
        CACHE STRING "Enabled build types" FORCE)
  else()
    message(TRACE "User chose a specific build type, so we are using that")
    set(CMAKE_CONFIGURATION_TYPES
        ${CMAKE_BUILD_TYPE}
        CACHE STRING "Enabled build types" FORCE)
  endif()
endif()

include(${_project_options_SOURCE_DIR}/src/DynamicProjectOptions.cmake)

# as developer, keep your code clean and free of bugs
set(ENABLE_WARNING_AS_ERRORS_DEFAULT ON)
set(ENABLE_CLANG_TIDY_DEFAULT ON)
set(ENABLE_CPPCHECK_DEFAULT ON)
set(ENABLE_INCLUDE_WHAT_YOU_USE_DEFAULT ON)
set(ENABLE_SANITIZER_ADDRESS_DEFAULT OFF)

# Enable CCache
set(ENABLE_CACHE_DEFAULT ON)
# generate doxygen
set(ENABLE_DOXYGEN_DEFAULT OFF)

dynamic_project_options()

target_compile_features(project_options INTERFACE cxx_std_${CMAKE_CXX_STANDARD})

set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} ${CMAKE_MODULE_PATH})
set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR} ${CMAKE_PREFIX_PATH})

# Adding project sources
add_subdirectory(src)

# # Adding the tests:
# option(OPT_ENABLE_TESTING "Enable the tests" ON)
# if(OPT_ENABLE_TESTING)
#   enable_testing()
#   message("Building Tests. Be sure to check out test/constexpr_tests for constexpr
# testing")
#   add_subdirectory(test)
# endif()

