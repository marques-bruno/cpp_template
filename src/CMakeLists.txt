cmake_minimum_required(VERSION 3.16)

# Add your executable's dependencies
find_package(CLI11 CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_subdirectory(${PROJECT_NAME})

add_executable(run_${PROJECT_NAME} main.cpp)

target_link_libraries(run_${PROJECT_NAME} PRIVATE
  myproject_lib
  CLI11::CLI11
  fmt::fmt
  spdlog::spdlog
)

target_include_directories(run_${PROJECT_NAME} PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")
