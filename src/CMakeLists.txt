cmake_minimum_required(VERSION 3.16)

# Add build dir to CMAKE's MODULE and PREFIX path
# (to find conan's package config files)
set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} ${CMAKE_MODULE_PATH})
set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR} ${CMAKE_PREFIX_PATH})

# Add your executable's dependencies
find_package(CLI11 CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_executable(myproject main.cpp)

target_link_libraries(myproject
  PUBLIC
  CLI11::CLI11
  fmt::fmt
  spdlog::spdlog
)

