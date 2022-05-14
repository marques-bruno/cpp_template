set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} ${CMAKE_MODULE_PATH})
set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR} ${CMAKE_PREFIX_PATH})

#Add your executable's dependencies
find_package(CLI11 REQUIRED)
find_package(fmt REQUIRED)

add_executable(myproject main.cpp)

target_link_libraries(myproject
  PRIVATE
  CLI11::CLI11
  fmt::fmt
)

